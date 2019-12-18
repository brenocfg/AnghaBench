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
typedef  int OPJ_SIZE_T ;
typedef  int OPJ_INT32 ;

/* Variables and functions */

__attribute__((used)) static void opj_dwt_deinterleave_v(OPJ_INT32 *a, OPJ_INT32 *b, OPJ_INT32 dn,
                                   OPJ_INT32 sn, OPJ_INT32 x, OPJ_INT32 cas)
{
    OPJ_INT32 i = sn;
    OPJ_INT32 * l_dest = b;
    OPJ_INT32 * l_src = a + cas;

    while (i--) {
        *l_dest = *l_src;
        l_dest += x;
        l_src += 2;
    } /* b[i*x]=a[2*i+cas]; */

    l_dest = b + (OPJ_SIZE_T)sn * (OPJ_SIZE_T)x;
    l_src = a + 1 - cas;

    i = dn;
    while (i--) {
        *l_dest = *l_src;
        l_dest += x;
        l_src += 2;
    } /*b[(sn+i)*x]=a[(2*i+1-cas)];*/
}