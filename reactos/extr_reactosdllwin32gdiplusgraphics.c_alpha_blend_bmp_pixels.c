#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ image; } ;
typedef  int PixelFormat ;
typedef  int INT ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpGraphics ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  GdipBitmapGetPixel (int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  GdipBitmapSetPixel (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ok ; 
 int const PixelFormatPAlpha ; 
 int /*<<< orphan*/  color_over (int,int) ; 
 int /*<<< orphan*/  color_over_fgpremult (int,int) ; 

__attribute__((used)) static GpStatus alpha_blend_bmp_pixels(GpGraphics *graphics, INT dst_x, INT dst_y,
    const BYTE *src, INT src_width, INT src_height, INT src_stride, const PixelFormat fmt)
{
    GpBitmap *dst_bitmap = (GpBitmap*)graphics->image;
    INT x, y;

    for (y=0; y<src_height; y++)
    {
        for (x=0; x<src_width; x++)
        {
            ARGB dst_color, src_color;
            src_color = ((ARGB*)(src + src_stride * y))[x];

            if (!(src_color & 0xff000000))
                continue;

            GdipBitmapGetPixel(dst_bitmap, x+dst_x, y+dst_y, &dst_color);
            if (fmt & PixelFormatPAlpha)
                GdipBitmapSetPixel(dst_bitmap, x+dst_x, y+dst_y, color_over_fgpremult(dst_color, src_color));
            else
                GdipBitmapSetPixel(dst_bitmap, x+dst_x, y+dst_y, color_over(dst_color, src_color));
        }
    }

    return Ok;
}