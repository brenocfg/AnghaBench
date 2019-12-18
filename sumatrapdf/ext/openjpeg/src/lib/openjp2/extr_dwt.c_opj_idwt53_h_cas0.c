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
typedef  int OPJ_UINT32 ;
typedef  size_t OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 

__attribute__((used)) static void  opj_idwt53_h_cas0(OPJ_INT32* tmp,
                               const OPJ_INT32 sn,
                               const OPJ_INT32 len,
                               OPJ_INT32* tiledp)
{
    OPJ_INT32 i, j;
    const OPJ_INT32* in_even = &tiledp[0];
    const OPJ_INT32* in_odd = &tiledp[sn];

#ifdef TWO_PASS_VERSION
    /* For documentation purpose: performs lifting in two iterations, */
    /* but without explicit interleaving */

    assert(len > 1);

    /* Even */
    tmp[0] = in_even[0] - ((in_odd[0] + 1) >> 1);
    for (i = 2, j = 0; i <= len - 2; i += 2, j++) {
        tmp[i] = in_even[j + 1] - ((in_odd[j] + in_odd[j + 1] + 2) >> 2);
    }
    if (len & 1) { /* if len is odd */
        tmp[len - 1] = in_even[(len - 1) / 2] - ((in_odd[(len - 2) / 2] + 1) >> 1);
    }

    /* Odd */
    for (i = 1, j = 0; i < len - 1; i += 2, j++) {
        tmp[i] = in_odd[j] + ((tmp[i - 1] + tmp[i + 1]) >> 1);
    }
    if (!(len & 1)) { /* if len is even */
        tmp[len - 1] = in_odd[(len - 1) / 2] + tmp[len - 2];
    }
#else
    OPJ_INT32 d1c, d1n, s1n, s0c, s0n;

    assert(len > 1);

    /* Improved version of the TWO_PASS_VERSION: */
    /* Performs lifting in one single iteration. Saves memory */
    /* accesses and explicit interleaving. */
    s1n = in_even[0];
    d1n = in_odd[0];
    s0n = s1n - ((d1n + 1) >> 1);

    for (i = 0, j = 1; i < (len - 3); i += 2, j++) {
        d1c = d1n;
        s0c = s0n;

        s1n = in_even[j];
        d1n = in_odd[j];

        s0n = s1n - ((d1c + d1n + 2) >> 2);

        tmp[i  ] = s0c;
        tmp[i + 1] = d1c + ((s0c + s0n) >> 1);
    }

    tmp[i] = s0n;

    if (len & 1) {
        tmp[len - 1] = in_even[(len - 1) / 2] - ((d1n + 1) >> 1);
        tmp[len - 2] = d1n + ((s0n + tmp[len - 1]) >> 1);
    } else {
        tmp[len - 1] = d1n + s0n;
    }
#endif
    memcpy(tiledp, tmp, (OPJ_UINT32)len * sizeof(OPJ_INT32));
}