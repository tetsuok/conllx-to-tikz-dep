// Copyright 2012 Tetsuo Kiso. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "token.h"
#include "sentence.h"
#include "util.h"
#include "blocks.h"
#include "latex_helper.h"

#include <fstream>
#include <iostream>
#include <cstring>

namespace conll {

const int kBufSize = 4096;

class Reader {
 public:
  Reader() : is_(NULL), sent_(sentence_new()) {}
  ~Reader() {
    if (is_ != &std::cin) {
      delete is_;
    }
    if (sent_ != NULL) {
      sentence_destroy(sent_);
    }
  }

  bool Open(const char* filename);

 private:
  int Tokenize(char* line, const char** seq, const char* sep) const {
    int i = 0;
    char* t = NULL;
    char* ptr = line;
    while ((t = strsep(&ptr, sep)) != NULL) {
      seq[i] = t;
      i++;
    }
    return i;
  }

  std::istream *is_;
  struct sentence* sent_;

  // no copying allowed.
  Reader(const Reader&);
  void operator=(const Reader&);
};

bool Reader::Open(const char* filename) {
    if (strncmp(filename, "-", strlen(filename)) == 0) {
      is_ = &std::cin;
    } else {
      is_ = new std::ifstream(filename);
    }

    if (!*is_) {
      std::cerr << "Cannot open: " << filename << std::endl;
      return false;
    }

    unsigned int num_sent = 0;
    unsigned int line_num = 0;
    const char* seq[CONLLX_TOKEN_NUM_FIELDS];
    const char* sep = "\t";
    char* line = new char[kBufSize];

    while (is_->getline(line, kBufSize)) {
      if (std::strlen(line) == 0) {
        latex_print_dep_tree(sent_);
        sentence_destroy(sent_);
        sent_ = sentence_new();
        num_sent++;
        continue;
      }

      const int n = Tokenize(line, seq, sep);
      if (n != CONLLX_TOKEN_NUM_FIELDS) {
        std::cerr << "File format is broken at line " << line_num << std::endl;
        return false;
      }
      sentence_add_token(sent_, token_new(seq, CONLLX_TOKEN_NUM_FIELDS));
      ++line_num;
    }
    delete [] line;
    std::cerr << "INFO: Number of sentences = " << num_sent << std::endl;
    return true;
}

} // namespace conll

int main(int argc, char** argv) {
  const char* filename = NULL;
  if (argc == 1) {
    filename = "-";
  } else if (argc == 2) {
    filename = argv[1];
  } else {
    std::cerr << "Usage: " << argv[0] << "filename" << std::endl;
    return -1;
  }

  conll::Reader rd;
  latex_print_header();
  if (!rd.Open(filename)) {
    std::cerr << "ERROR: failed to open " << filename << std::endl;
    return -1;
  }
  latex_print_footer();

  return 0;
}
