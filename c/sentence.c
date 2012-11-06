/* Copyright 2012 Tetsuo Kiso. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include "sentence.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "util.h"

const int kBufSize = 256;

struct sentence* sentence_new(void)
{
    struct sentence* s = xmalloc(sizeof(struct sentence));
    s->length = 0;
    s->cap = kBufSize;
    s->tokens = xmalloc(sizeof(struct token *) * kBufSize);
    return s;
}

void sentence_destroy(struct sentence* s)
{
    if (s == NULL) return;
    int i;
    for (i = 0; i < s->length; i++) {
        token_destroy(s->tokens[i]);
    }
    free(s->tokens);
    free(s);
}

void sentence_add_token(struct sentence* s, struct token* t)
{
    if (s == NULL || t == NULL) return;
    if (s->length >= s->cap) {
        struct token* new_tokens = xmalloc(sizeof(struct token *) * (unsigned long)s->cap * 2);
        memcpy(new_tokens, s->tokens, s->cap);
        s->cap *= 2;
    }
    s->tokens[s->length] = t;
    s->length++;
}

void print_form(const struct sentence* s)
{
    int i;
    for (i = 0; i < s->length; i++) {
        if (i > 0) printf(" ");
        printf("%s", s->tokens[i]->form);
    }
    printf("\n");
}
