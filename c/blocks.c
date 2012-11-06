/* Copyright 2012 Tetsuo Kiso. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#include "blocks.h"

#include <stdlib.h>
#include <string.h>
#include "util.h"

struct blocks* new_blocks(int size)
{
    int i;
    struct blocks* b = xmalloc(sizeof(struct blocks));
    b->bufs = xmalloc(sizeof(char *) * (unsigned long)size);
    for (i = 0; i < size; i++) {
        b->bufs[i] = NULL;
    }
    b->size = size;
    b->ptr = 0;
    return b;
}

void destroy_blocks(struct blocks* b)
{
    int i;
    for (i = 0; i < b->ptr; i++) {
        if (b->bufs[i] != NULL)
            free(b->bufs[i]);
    }
    free(b->bufs);
    free(b);
}

void blocks_add_elem(struct blocks* b, char* s)
{
    if (b->ptr >= b->size) {
        char** new_bufs = xmalloc(sizeof(char *) * (unsigned long)b->size * 2);
        memcpy(new_bufs, b->bufs, b->size);
        b->bufs = new_bufs;
        b->size *= 2;
    }
    b->bufs[b->ptr] = s;
    b->ptr++;
}
