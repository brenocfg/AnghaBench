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
typedef  int OPJ_UINT8 ;
typedef  int OPJ_UINT32 ;
typedef  unsigned int OPJ_SIZE_T ;
typedef  scalar_t__ OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */

__attribute__((used)) static void convert_4u32s_C1R(const OPJ_BYTE* pSrc, OPJ_INT32* pDst,
                              OPJ_SIZE_T length)
{
    OPJ_SIZE_T i;
    for (i = 0; i < (length & ~(OPJ_SIZE_T)1U); i += 2U) {
        OPJ_UINT32 val = *pSrc++;
        pDst[i + 0] = (OPJ_INT32)(val >> 4);
        pDst[i + 1] = (OPJ_INT32)(val & 0xFU);
    }
    if (length & 1U) {
        OPJ_UINT8 val = *pSrc++;
        pDst[i + 0] = (OPJ_INT32)(val >> 4);
    }
}