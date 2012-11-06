/* Copyright 2012 Tetsuo Kiso. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef CONLLX_TO_TIKZ_DEP_SENTENCE_H_
#define CONLLX_TO_TIKZ_DEP_SENTENCE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct token;

struct sentence {
  int length;
  int cap;
  struct token** tokens;
};

struct sentence* sentence_new(void);

void sentence_destroy(struct sentence* s);

void sentence_add_token(struct sentence* s, struct token* t);

void print_form(const struct sentence* s);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CONLLX_TO_TIKZ_DEP_SENTENCE_H_ */
