#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int OPJ_UINT32 ;

/* Variables and functions */

__attribute__((used)) static void bmp_mask_get_shift_and_prec(OPJ_UINT32 mask, OPJ_UINT32* shift,
                                        OPJ_UINT32* prec)
{
    OPJ_UINT32 l_shift, l_prec;

    l_shift = l_prec = 0U;

    if (mask != 0U) {
        while ((mask & 1U) == 0U) {
            mask >>= 1;
            l_shift++;
        }
        while (mask & 1U) {
            mask >>= 1;
            l_prec++;
        }
    }
    *shift = l_shift;
    *prec = l_prec;
}