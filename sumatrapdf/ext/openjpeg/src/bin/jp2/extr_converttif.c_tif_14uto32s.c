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

__attribute__((used)) static void tif_14uto32s(const OPJ_BYTE* pSrc, OPJ_INT32* pDst,
                         OPJ_SIZE_T length)
{
    OPJ_SIZE_T i;
    for (i = 0; i < (length & ~(OPJ_SIZE_T)3U); i += 4U) {
        OPJ_UINT32 val0 = *pSrc++;
        OPJ_UINT32 val1 = *pSrc++;
        OPJ_UINT32 val2 = *pSrc++;
        OPJ_UINT32 val3 = *pSrc++;
        OPJ_UINT32 val4 = *pSrc++;
        OPJ_UINT32 val5 = *pSrc++;
        OPJ_UINT32 val6 = *pSrc++;

        pDst[i + 0] = (OPJ_INT32)((val0 << 6) | (val1 >> 2));
        pDst[i + 1] = (OPJ_INT32)(((val1 & 0x3U) << 12) | (val2 << 4) | (val3 >> 4));
        pDst[i + 2] = (OPJ_INT32)(((val3 & 0xFU) << 10) | (val4 << 2) | (val5 >> 6));
        pDst[i + 3] = (OPJ_INT32)(((val5 & 0x3FU) << 8) | val6);

    }
    if (length & 3U) {
        OPJ_UINT32 val0 = *pSrc++;
        OPJ_UINT32 val1 = *pSrc++;
        length = length & 3U;
        pDst[i + 0] = (OPJ_INT32)((val0 << 6) | (val1 >> 2));

        if (length > 1U) {
            OPJ_UINT32 val2 = *pSrc++;
            OPJ_UINT32 val3 = *pSrc++;
            pDst[i + 1] = (OPJ_INT32)(((val1 & 0x3U) << 12) | (val2 << 4) | (val3 >> 4));
            if (length > 2U) {
                OPJ_UINT32 val4 = *pSrc++;
                OPJ_UINT32 val5 = *pSrc++;
                pDst[i + 2] = (OPJ_INT32)(((val3 & 0xFU) << 10) | (val4 << 2) | (val5 >> 6));
            }
        }
    }
}