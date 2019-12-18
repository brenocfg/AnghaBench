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
typedef  size_t OPJ_UINT8 ;
typedef  unsigned int OPJ_UINT32 ;
typedef  scalar_t__ OPJ_INT32 ;

/* Variables and functions */

__attribute__((used)) static void opj_applyLUT8u_8u32s_C1P3R(
    OPJ_UINT8 const* pSrc, OPJ_INT32 srcStride,
    OPJ_INT32* const* pDst, OPJ_INT32 const* pDstStride,
    OPJ_UINT8 const* const* pLUT,
    OPJ_UINT32 width, OPJ_UINT32 height)
{
    OPJ_UINT32 y;
    OPJ_INT32* pR = pDst[0];
    OPJ_INT32* pG = pDst[1];
    OPJ_INT32* pB = pDst[2];
    OPJ_UINT8 const* pLUT_R = pLUT[0];
    OPJ_UINT8 const* pLUT_G = pLUT[1];
    OPJ_UINT8 const* pLUT_B = pLUT[2];

    for (y = height; y != 0U; --y) {
        OPJ_UINT32 x;

        for (x = 0; x < width; x++) {
            OPJ_UINT8 idx = pSrc[x];
            pR[x] = (OPJ_INT32)pLUT_R[idx];
            pG[x] = (OPJ_INT32)pLUT_G[idx];
            pB[x] = (OPJ_INT32)pLUT_B[idx];
        }
        pSrc += srcStride;
        pR += pDstStride[0];
        pG += pDstStride[1];
        pB += pDstStride[2];
    }
}