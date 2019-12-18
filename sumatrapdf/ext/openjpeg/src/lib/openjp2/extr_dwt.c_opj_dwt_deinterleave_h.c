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
typedef  int OPJ_INT32 ;

/* Variables and functions */

__attribute__((used)) static void opj_dwt_deinterleave_h(OPJ_INT32 *a, OPJ_INT32 *b, OPJ_INT32 dn,
                                   OPJ_INT32 sn, OPJ_INT32 cas)
{
    OPJ_INT32 i;
    OPJ_INT32 * l_dest = b;
    OPJ_INT32 * l_src = a + cas;

    for (i = 0; i < sn; ++i) {
        *l_dest++ = *l_src;
        l_src += 2;
    }

    l_dest = b + sn;
    l_src = a + 1 - cas;

    for (i = 0; i < dn; ++i)  {
        *l_dest++ = *l_src;
        l_src += 2;
    }
}