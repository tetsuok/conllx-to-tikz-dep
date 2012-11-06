/* Copyright 2012 Tetsuo Kiso. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "sentence.h"
#include "util.h"
#include "blocks.h"
#include "latex_helper.h"

#define BUF_SIZE 8192

static int read_conllx(FILE* fp)
{
    int num_sent = 0;
    unsigned int line_num = 0;
    char buff[BUF_SIZE];
    const char* sep = "\t";
    char *t, *line, *tofree;
    size_t len;

    const char** seq = xmalloc(sizeof(char *) * CONLLX_TOKEN_NUM_FIELDS);
    struct blocks* blocks = new_blocks(256);
    struct sentence* sent = sentence_new();

    while (fgets(buff, sizeof(buff), fp)) {
        line_num++;
        if (buff[0] == '\n') {
            latex_print_dep_tree(sent);
            sentence_destroy(sent);
            sent = sentence_new();
            num_sent++;
            continue;
        }
        len = strnlen(buff, BUF_SIZE);
        tofree = line = strndup(buff, len-1);
        blocks_add_elem(blocks, tofree);

        int i = 0;
        while ((t = strsep(&line, sep)) != NULL) {
            seq[i] = t;
            i++;
        }
        sentence_add_token(sent, token_new(seq, CONLLX_TOKEN_NUM_FIELDS));
    }
    destroy_blocks(blocks);
    sentence_destroy(sent);
    free(seq);
    fprintf(stderr, "INFO: Number of sentences = %d\n", num_sent);

    return 0;
}

static int open_conllx(const char* filename)
{
    FILE* fp;

    if (strncmp(filename, "-", strlen(filename)) == 0) {
        fp = stdin;
    } else {
        fp = fopen(filename, "r");
        if (fp == NULL) {
            fprintf(stderr, "no such file or directory: %s\n", filename);
            return -1;
        }
    }

    if (read_conllx(fp) == -1) {
        fprintf(stderr, "Failed to read %s\n", filename);
        return -1;
    }
    fclose(fp);
    return 0;
}

int main(int argc, char** argv)
{
    const char* filename = NULL;
    if (argc == 1) {
        filename = "-";
    } else if (argc == 2) {
        filename = argv[1];
    } else {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return -1;
    }
    latex_print_header();
    if (open_conllx(filename) != 0) {
        fprintf(stderr, "ERROR: failed to open %s\n", argv[1]);
        return -1;
    }
    latex_print_footer();
    return 0;
}
