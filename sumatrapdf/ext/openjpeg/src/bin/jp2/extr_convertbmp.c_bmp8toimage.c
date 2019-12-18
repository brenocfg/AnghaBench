#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int numcomps; TYPE_1__* comps; } ;
typedef  TYPE_2__ opj_image_t ;
struct TYPE_5__ {unsigned int w; unsigned int h; scalar_t__* data; } ;
typedef  int /*<<< orphan*/  OPJ_UINT8 ;
typedef  unsigned int OPJ_UINT32 ;
typedef  scalar_t__ OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  opj_applyLUT8u_8u32s_C1P3R (int /*<<< orphan*/  const*,scalar_t__,scalar_t__**,scalar_t__*,int /*<<< orphan*/  const* const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  opj_applyLUT8u_8u32s_C1R (int /*<<< orphan*/  const*,scalar_t__,scalar_t__*,scalar_t__,int /*<<< orphan*/  const* const,unsigned int,unsigned int) ; 

__attribute__((used)) static opj_image_t* bmp8toimage(const OPJ_UINT8* pData, OPJ_UINT32 stride,
                                opj_image_t* image, OPJ_UINT8 const* const* pLUT)
{
    OPJ_UINT32 width, height;
    const OPJ_UINT8 *pSrc = NULL;

    width  = image->comps[0].w;
    height = image->comps[0].h;

    pSrc = pData + (height - 1U) * stride;
    if (image->numcomps == 1U) {
        opj_applyLUT8u_8u32s_C1R(pSrc, -(OPJ_INT32)stride, image->comps[0].data,
                                 (OPJ_INT32)width, pLUT[0], width, height);
    } else {
        OPJ_INT32* pDst[3];
        OPJ_INT32  pDstStride[3];

        pDst[0] = image->comps[0].data;
        pDst[1] = image->comps[1].data;
        pDst[2] = image->comps[2].data;
        pDstStride[0] = (OPJ_INT32)width;
        pDstStride[1] = (OPJ_INT32)width;
        pDstStride[2] = (OPJ_INT32)width;
        opj_applyLUT8u_8u32s_C1P3R(pSrc, -(OPJ_INT32)stride, pDst, pDstStride, pLUT,
                                   width, height);
    }
    return image;
}