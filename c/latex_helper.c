/* Copyright 2012 Tetsuo Kiso. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include "latex_helper.h"
#include "sentence.h"
#include "token.h"

#include <stdio.h>

void latex_print_deptext(const struct sentence* s)
{
    int i;

    printf("\\begin{deptext}[column sep=1em]\n");
    for (i = 0; i < s->length; i++) {
        if (i > 0) printf(" \\& ");
        printf("%s", s->tokens[i]->form);
    }
    puts(" \\\\");
    puts("\\end{deptext}");
}

void latex_print_depedge(int h, int m)
{
    printf("\\depedge{%d}{%d}{}\n", h, m);
}

void latex_print_header(void)
{
    puts("\\documentclass{standalone}");
    puts("\\usepackage{tikz-dependency}");
    puts("\\begin{document}");
    puts("\\begin{dependency}[theme = simple]");
}

void latex_print_footer(void)
{
    puts("\\end{dependency}");
    puts("\\end{document}");
}

void latex_print_dep_tree(const struct sentence* s)
{
    int i;
    latex_print_deptext(s);
    for (i = 0; i < s->length; i++) {
        if (is_root(s->tokens[i])) continue;
        latex_print_depedge(s->tokens[i]->head, s->tokens[i]->id);
    }
}
