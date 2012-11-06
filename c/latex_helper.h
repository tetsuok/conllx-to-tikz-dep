/* Copyright 2012 Tetsuo Kiso. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef CONLLX_TO_TIKZ_DEP_LATEX_HELPER_H_
#define CONLLX_TO_TIKZ_DEP_LATEX_HELPER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct sentence;

void latex_print_deptext(const struct sentence* s);

void latex_print_depedge(int h, int m);

void latex_print_header(void);

void latex_print_footer(void);

void latex_print_dep_tree(const struct sentence* s);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CONLLX_TO_TIKZ_DEP_LATEX_HELPER_H_ */
