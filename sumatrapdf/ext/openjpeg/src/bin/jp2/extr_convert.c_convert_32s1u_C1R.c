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
typedef  void* OPJ_BYTE ;

/* Variables and functions */

__attribute__((used)) static void convert_32s1u_C1R(const OPJ_INT32* pSrc, OPJ_BYTE* pDst,
                              OPJ_SIZE_T length)
{
    OPJ_SIZE_T i;
    for (i = 0; i < (length & ~(OPJ_SIZE_T)7U); i += 8U) {
        OPJ_UINT32 src0 = (OPJ_UINT32)pSrc[i + 0];
        OPJ_UINT32 src1 = (OPJ_UINT32)pSrc[i + 1];
        OPJ_UINT32 src2 = (OPJ_UINT32)pSrc[i + 2];
        OPJ_UINT32 src3 = (OPJ_UINT32)pSrc[i + 3];
        OPJ_UINT32 src4 = (OPJ_UINT32)pSrc[i + 4];
        OPJ_UINT32 src5 = (OPJ_UINT32)pSrc[i + 5];
        OPJ_UINT32 src6 = (OPJ_UINT32)pSrc[i + 6];
        OPJ_UINT32 src7 = (OPJ_UINT32)pSrc[i + 7];

        *pDst++ = (OPJ_BYTE)((src0 << 7) | (src1 << 6) | (src2 << 5) | (src3 << 4) |
                             (src4 << 3) | (src5 << 2) | (src6 << 1) | src7);
    }

    if (length & 7U) {
        OPJ_UINT32 src0 = (OPJ_UINT32)pSrc[i + 0];
        OPJ_UINT32 src1 = 0U;
        OPJ_UINT32 src2 = 0U;
        OPJ_UINT32 src3 = 0U;
        OPJ_UINT32 src4 = 0U;
        OPJ_UINT32 src5 = 0U;
        OPJ_UINT32 src6 = 0U;
        length = length & 7U;

        if (length > 1U) {
            src1 = (OPJ_UINT32)pSrc[i + 1];
            if (length > 2U) {
                src2 = (OPJ_UINT32)pSrc[i + 2];
                if (length > 3U) {
                    src3 = (OPJ_UINT32)pSrc[i + 3];
                    if (length > 4U) {
                        src4 = (OPJ_UINT32)pSrc[i + 4];
                        if (length > 5U) {
                            src5 = (OPJ_UINT32)pSrc[i + 5];
                            if (length > 6U) {
                                src6 = (OPJ_UINT32)pSrc[i + 6];
                            }
                        }
                    }
                }
            }
        }
        *pDst++ = (OPJ_BYTE)((src0 << 7) | (src1 << 6) | (src2 << 5) | (src3 << 4) |
                             (src4 << 3) | (src5 << 2) | (src6 << 1));
    }
}