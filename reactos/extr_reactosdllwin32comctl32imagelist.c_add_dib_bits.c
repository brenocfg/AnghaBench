#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int biWidth; } ;
struct TYPE_14__ {TYPE_1__ bmiHeader; } ;
struct TYPE_13__ {int* has_alpha; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  hdcMask; int /*<<< orphan*/  hdcImage; scalar_t__ hbmMask; } ;
struct TYPE_12__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ POINT ;
typedef  TYPE_3__* HIMAGELIST ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;
typedef  TYPE_4__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int FALSE ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  StretchDIBits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imagelist_point_from_index (TYPE_3__*,int,TYPE_2__*) ; 

__attribute__((used)) static void add_dib_bits( HIMAGELIST himl, int pos, int count, int width, int height,
                          BITMAPINFO *info, BITMAPINFO *mask_info, DWORD *bits, BYTE *mask_bits )
{
    int i, j, n;
    POINT pt;
    int stride = info->bmiHeader.biWidth;
    int mask_stride = (info->bmiHeader.biWidth + 31) / 32 * 4;

    for (n = 0; n < count; n++)
    {
        BOOL has_alpha = FALSE;

        imagelist_point_from_index( himl, pos + n, &pt );

        /* check if bitmap has an alpha channel */
        for (i = 0; i < height && !has_alpha; i++)
            for (j = n * width; j < (n + 1) * width; j++)
                if ((has_alpha = ((bits[i * stride + j] & 0xff000000) != 0))) break;

        if (!has_alpha)  /* generate alpha channel from the mask */
        {
            for (i = 0; i < height; i++)
                for (j = n * width; j < (n + 1) * width; j++)
                    if (!mask_info || !((mask_bits[i * mask_stride + j / 8] << (j % 8)) & 0x80))
                        bits[i * stride + j] |= 0xff000000;
                    else
                        bits[i * stride + j] = 0;
        }
        else
        {
            himl->has_alpha[pos + n] = 1;

            if (mask_info && himl->hbmMask)  /* generate the mask from the alpha channel */
            {
                for (i = 0; i < height; i++)
                    for (j = n * width; j < (n + 1) * width; j++)
                        if ((bits[i * stride + j] >> 24) > 25) /* more than 10% alpha */
                            mask_bits[i * mask_stride + j / 8] &= ~(0x80 >> (j % 8));
                        else
                            mask_bits[i * mask_stride + j / 8] |= 0x80 >> (j % 8);
            }
        }
        StretchDIBits( himl->hdcImage, pt.x, pt.y, himl->cx, himl->cy,
                       n * width, 0, width, height, bits, info, DIB_RGB_COLORS, SRCCOPY );
        if (mask_info)
            StretchDIBits( himl->hdcMask, pt.x, pt.y, himl->cx, himl->cy,
                           n * width, 0, width, height, mask_bits, mask_info, DIB_RGB_COLORS, SRCCOPY );
    }
}