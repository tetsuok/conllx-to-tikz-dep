/* Copyright 2012 Tetsuo Kiso. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include "util.h"

#include <string.h>
#include <stdio.h>

void* xmalloc(size_t n) {
    void *p = (void *)malloc(n);
    if (p == NULL) {
        fprintf(stderr, "memory exhausted!\n");
        exit(-1);
    }
    return p;
}
