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
typedef  unsigned int OPJ_SIZE_T ;
typedef  scalar_t__ OPJ_INT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */

__attribute__((used)) static void convert_1u32s_C1R(const OPJ_BYTE* pSrc, OPJ_INT32* pDst,
                              OPJ_SIZE_T length)
{
    OPJ_SIZE_T i;
    for (i = 0; i < (length & ~(OPJ_SIZE_T)7U); i += 8U) {
        OPJ_UINT32 val = *pSrc++;
        pDst[i + 0] = (OPJ_INT32)(val >> 7);
        pDst[i + 1] = (OPJ_INT32)((val >> 6) & 0x1U);
        pDst[i + 2] = (OPJ_INT32)((val >> 5) & 0x1U);
        pDst[i + 3] = (OPJ_INT32)((val >> 4) & 0x1U);
        pDst[i + 4] = (OPJ_INT32)((val >> 3) & 0x1U);
        pDst[i + 5] = (OPJ_INT32)((val >> 2) & 0x1U);
        pDst[i + 6] = (OPJ_INT32)((val >> 1) & 0x1U);
        pDst[i + 7] = (OPJ_INT32)(val & 0x1U);
    }
    if (length & 7U) {
        OPJ_UINT32 val = *pSrc++;
        length = length & 7U;
        pDst[i + 0] = (OPJ_INT32)(val >> 7);

        if (length > 1U) {
            pDst[i + 1] = (OPJ_INT32)((val >> 6) & 0x1U);
            if (length > 2U) {
                pDst[i + 2] = (OPJ_INT32)((val >> 5) & 0x1U);
                if (length > 3U) {
                    pDst[i + 3] = (OPJ_INT32)((val >> 4) & 0x1U);
                    if (length > 4U) {
                        pDst[i + 4] = (OPJ_INT32)((val >> 3) & 0x1U);
                        if (length > 5U) {
                            pDst[i + 5] = (OPJ_INT32)((val >> 2) & 0x1U);
                            if (length > 6U) {
                                pDst[i + 6] = (OPJ_INT32)((val >> 1) & 0x1U);
                            }
                        }
                    }
                }
            }
        }
    }
}