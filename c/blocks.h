/* Copyright 2012 Tetsuo Kiso. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef CONLLX_TO_TIKZ_DEP_BLOCKS_H_
#define CONLLX_TO_TIKZ_DEP_BLOCKS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct blocks {
    char** bufs;                        /* takes the ownership for each char array. */
    int size;
    int ptr;
};

struct blocks* new_blocks(int size);

void destroy_blocks(struct blocks* b);

void blocks_add_elem(struct blocks* b, char* s);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CONLLX_TO_TIKZ_DEP_BLOCKS_H_ */
