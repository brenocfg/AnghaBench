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
typedef  scalar_t__ OPJ_SIZE_T ;
typedef  int OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */

__attribute__((used)) static void convert_16u32s_C1R(const OPJ_BYTE* pSrc, OPJ_INT32* pDst,
                               OPJ_SIZE_T length)
{
    OPJ_SIZE_T i;
    for (i = 0; i < length; i++) {
        OPJ_INT32 val0 = *pSrc++;
        OPJ_INT32 val1 = *pSrc++;
        pDst[i] = val0 << 8 | val1;
    }
}