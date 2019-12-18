#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_4__ {unsigned int n_bitmaps; int* bitmaps; int /*<<< orphan*/  bitmaps_allocated; } ;
typedef  TYPE_1__ Bitmap ;

/* Variables and functions */
 unsigned int BITMAPS_MAX_ENTRY ; 
 unsigned int BITMAP_NUM_TO_OFFSET (unsigned int) ; 
 int BITMAP_NUM_TO_REM (unsigned int) ; 
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  GREEDY_REALLOC0 (int*,int /*<<< orphan*/ ,unsigned int) ; 
 int UINT64_C (int) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

int bitmap_set(Bitmap *b, unsigned n) {
        uint64_t bitmask;
        unsigned offset;

        assert(b);

        /* we refuse to allocate huge bitmaps */
        if (n > BITMAPS_MAX_ENTRY)
                return -ERANGE;

        offset = BITMAP_NUM_TO_OFFSET(n);

        if (offset >= b->n_bitmaps) {
                if (!GREEDY_REALLOC0(b->bitmaps, b->bitmaps_allocated, offset + 1))
                        return -ENOMEM;

                b->n_bitmaps = offset + 1;
        }

        bitmask = UINT64_C(1) << BITMAP_NUM_TO_REM(n);

        b->bitmaps[offset] |= bitmask;

        return 0;
}