#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {unsigned int n_bitmaps; int* bitmaps; } ;
typedef  TYPE_1__ Bitmap ;

/* Variables and functions */
 unsigned int BITMAP_NUM_TO_OFFSET (unsigned int) ; 
 int BITMAP_NUM_TO_REM (unsigned int) ; 
 int UINT64_C (int) ; 

void bitmap_unset(Bitmap *b, unsigned n) {
        uint64_t bitmask;
        unsigned offset;

        if (!b)
                return;

        offset = BITMAP_NUM_TO_OFFSET(n);

        if (offset >= b->n_bitmaps)
                return;

        bitmask = UINT64_C(1) << BITMAP_NUM_TO_REM(n);

        b->bitmaps[offset] &= ~bitmask;
}