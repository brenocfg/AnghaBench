#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* comps; } ;
typedef  TYPE_2__ opj_image_t ;
struct TYPE_4__ {unsigned int w; unsigned int h; void** data; } ;
typedef  scalar_t__ OPJ_UINT8 ;
typedef  unsigned int OPJ_UINT32 ;
typedef  void* OPJ_INT32 ;

/* Variables and functions */

__attribute__((used)) static void bmp24toimage(const OPJ_UINT8* pData, OPJ_UINT32 stride,
                         opj_image_t* image)
{
    int index;
    OPJ_UINT32 width, height;
    OPJ_UINT32 x, y;
    const OPJ_UINT8 *pSrc = NULL;

    width  = image->comps[0].w;
    height = image->comps[0].h;

    index = 0;
    pSrc = pData + (height - 1U) * stride;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            image->comps[0].data[index] = (OPJ_INT32)pSrc[3 * x + 2]; /* R */
            image->comps[1].data[index] = (OPJ_INT32)pSrc[3 * x + 1]; /* G */
            image->comps[2].data[index] = (OPJ_INT32)pSrc[3 * x + 0]; /* B */
            index++;
        }
        pSrc -= stride;
    }
}