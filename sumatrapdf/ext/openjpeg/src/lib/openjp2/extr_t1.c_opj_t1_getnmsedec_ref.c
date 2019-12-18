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
typedef  int /*<<< orphan*/  OPJ_INT16 ;

/* Variables and functions */
 int T1_NMSEDEC_BITS ; 
 int /*<<< orphan*/ * lut_nmsedec_ref ; 
 int /*<<< orphan*/ * lut_nmsedec_ref0 ; 

__attribute__((used)) static OPJ_INT16 opj_t1_getnmsedec_ref(OPJ_UINT32 x, OPJ_UINT32 bitpos)
{
    if (bitpos > 0) {
        return lut_nmsedec_ref[(x >> (bitpos)) & ((1 << T1_NMSEDEC_BITS) - 1)];
    }

    return lut_nmsedec_ref0[x & ((1 << T1_NMSEDEC_BITS) - 1)];
}