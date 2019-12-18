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
typedef  int /*<<< orphan*/  OPJ_INT32 ;
typedef  void* OPJ_BYTE ;

/* Variables and functions */

__attribute__((used)) static void tif_32sto12u(const OPJ_INT32* pSrc, OPJ_BYTE* pDst,
                         OPJ_SIZE_T length)
{
    OPJ_SIZE_T i;
    for (i = 0; i < (length & ~(OPJ_SIZE_T)1U); i += 2U) {
        OPJ_UINT32 src0 = (OPJ_UINT32)pSrc[i + 0];
        OPJ_UINT32 src1 = (OPJ_UINT32)pSrc[i + 1];

        *pDst++ = (OPJ_BYTE)(src0 >> 4);
        *pDst++ = (OPJ_BYTE)(((src0 & 0xFU) << 4) | (src1 >> 8));
        *pDst++ = (OPJ_BYTE)(src1);
    }

    if (length & 1U) {
        OPJ_UINT32 src0 = (OPJ_UINT32)pSrc[i + 0];
        *pDst++ = (OPJ_BYTE)(src0 >> 4);
        *pDst++ = (OPJ_BYTE)(((src0 & 0xFU) << 4));
    }
}