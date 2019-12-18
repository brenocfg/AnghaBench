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

__attribute__((used)) static void opj_idwt3_v_cas0(OPJ_INT32* tmp,
                             const OPJ_INT32 sn,
                             const OPJ_INT32 len,
                             OPJ_INT32* tiledp_col,
                             const OPJ_SIZE_T stride)
{
    OPJ_INT32 i, j;
    OPJ_INT32 d1c, d1n, s1n, s0c, s0n;

    assert(len > 1);

    /* Performs lifting in one single iteration. Saves memory */
    /* accesses and explicit interleaving. */

    s1n = tiledp_col[0];
    d1n = tiledp_col[(OPJ_SIZE_T)sn * stride];
    s0n = s1n - ((d1n + 1) >> 1);

    for (i = 0, j = 0; i < (len - 3); i += 2, j++) {
        d1c = d1n;
        s0c = s0n;

        s1n = tiledp_col[(OPJ_SIZE_T)(j + 1) * stride];
        d1n = tiledp_col[(OPJ_SIZE_T)(sn + j + 1) * stride];

        s0n = s1n - ((d1c + d1n + 2) >> 2);

        tmp[i  ] = s0c;
        tmp[i + 1] = d1c + ((s0c + s0n) >> 1);
    }

    tmp[i] = s0n;

    if (len & 1) {
        tmp[len - 1] =
            tiledp_col[(OPJ_SIZE_T)((len - 1) / 2) * stride] -
            ((d1n + 1) >> 1);
        tmp[len - 2] = d1n + ((s0n + tmp[len - 1]) >> 1);
    } else {
        tmp[len - 1] = d1n + s0n;
    }

    for (i = 0; i < len; ++i) {
        tiledp_col[(OPJ_SIZE_T)i * stride] = tmp[i];
    }
}