/* Copyright 2012 Tetsuo Kiso. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include "token.h"

#include <stdio.h>
#include "util.h"

struct token* token_new(const char** seq, int n)
{
    struct token* t;

    if (seq == NULL) {
        fprintf(stderr, "Warning: the pointer seq is NULL.\n");
        return NULL;
    }
    t = xmalloc(sizeof(struct token));

    if (n != CONLLX_TOKEN_NUM_FIELDS) {
        fprintf(stderr, "invalid data format: n = %d\n", n);
        return NULL;
    }

    t->id = atoi(seq[0]);
    t->form = seq[1];
    t->lemma = seq[2];
    t->cpos = seq[3];
    t->pos = seq[4];
    t->feat = seq[5];
    t->head = atoi(seq[6]);
    t->deprel = seq[7];
    t->phead = seq[8];
    t->pdeprel = seq[9];

    if (t->id < 0) {
        fprintf(stderr, "invalid id = %d\n", t->id);
        return NULL;
    }
    if (t->head < 0) {
        fprintf(stderr, "invalid head = %d\n", t->head);
        return NULL;
    }

    return t;
}

void token_destroy(struct token* t)
{
    if (t == NULL) return;
    free(t);
}

int is_root(const struct token* t)
{
    return (t != NULL) ? t->head == 0 : -1;
}
