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
typedef  size_t const OPJ_SIZE_T ;
typedef  int OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void opj_idwt3_v_cas1(OPJ_INT32* tmp,
                             const OPJ_INT32 sn,
                             const OPJ_INT32 len,
                             OPJ_INT32* tiledp_col,
                             const OPJ_SIZE_T stride)
{
    OPJ_INT32 i, j;
    OPJ_INT32 s1, s2, dc, dn;
    const OPJ_INT32* in_even = &tiledp_col[(OPJ_SIZE_T)sn * stride];
    const OPJ_INT32* in_odd = &tiledp_col[0];

    assert(len > 2);

    /* Performs lifting in one single iteration. Saves memory */
    /* accesses and explicit interleaving. */

    s1 = in_even[stride];
    dc = in_odd[0] - ((in_even[0] + s1 + 2) >> 2);
    tmp[0] = in_even[0] + dc;
    for (i = 1, j = 1; i < (len - 2 - !(len & 1)); i += 2, j++) {

        s2 = in_even[(OPJ_SIZE_T)(j + 1) * stride];

        dn = in_odd[(OPJ_SIZE_T)j * stride] - ((s1 + s2 + 2) >> 2);
        tmp[i  ] = dc;
        tmp[i + 1] = s1 + ((dn + dc) >> 1);

        dc = dn;
        s1 = s2;
    }
    tmp[i] = dc;
    if (!(len & 1)) {
        dn = in_odd[(OPJ_SIZE_T)(len / 2 - 1) * stride] - ((s1 + 1) >> 1);
        tmp[len - 2] = s1 + ((dn + dc) >> 1);
        tmp[len - 1] = dn;
    } else {
        tmp[len - 1] = s1 + dc;
    }

    for (i = 0; i < len; ++i) {
        tiledp_col[(OPJ_SIZE_T)i * stride] = tmp[i];
    }
}