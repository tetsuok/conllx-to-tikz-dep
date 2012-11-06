/* Copyright 2012 Tetsuo Kiso. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef CONLLX_TO_TIKZ_DEP_TOKEN_H_
#define CONLLX_TO_TIKZ_DEP_TOKEN_H_

#define CONLLX_TOKEN_NUM_FIELDS 10

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct token {
  int id;
  int head;
  const char* form;
  const char* lemma;
  const char* cpos;
  const char* pos;
  const char* feat;
  const char* deprel;
  const char* phead;
  const char* pdeprel;
};

struct token* token_new(const char** seq, int n);

void token_destroy(struct token* t);

int is_root(const struct token* t);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* CONLLX_TO_TIKZ_DEP_TOKEN_H_ */
