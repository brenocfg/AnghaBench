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
struct TYPE_6__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; scalar_t__ biClrImportant; scalar_t__ biClrUsed; scalar_t__ biYPelsPerMeter; scalar_t__ biXPelsPerMeter; scalar_t__ biSizeImage; int /*<<< orphan*/  biCompression; } ;
struct TYPE_5__ {int /*<<< orphan*/  hdc; } ;
typedef  int PixelFormat ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpGraphics ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_2__ BITMAPINFOHEADER ;
typedef  int /*<<< orphan*/  BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateDIBSection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 scalar_t__ DT_RASPRINTER ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 scalar_t__ GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ok ; 
 int PixelFormatPAlpha ; 
 scalar_t__ SB_NONE ; 
 int /*<<< orphan*/  SHADEBLENDCAPS ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TECHNOLOGY ; 
 int /*<<< orphan*/  convert_32bppARGB_to_32bppPARGB (int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  gdi_alpha_blend (TYPE_1__*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static GpStatus alpha_blend_hdc_pixels(GpGraphics *graphics, INT dst_x, INT dst_y,
    const BYTE *src, INT src_width, INT src_height, INT src_stride, PixelFormat fmt)
{
    HDC hdc;
    HBITMAP hbitmap;
    BITMAPINFOHEADER bih;
    BYTE *temp_bits;

    hdc = CreateCompatibleDC(0);

    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = src_width;
    bih.biHeight = -src_height;
    bih.biPlanes = 1;
    bih.biBitCount = 32;
    bih.biCompression = BI_RGB;
    bih.biSizeImage = 0;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;
    bih.biClrUsed = 0;
    bih.biClrImportant = 0;

    hbitmap = CreateDIBSection(hdc, (BITMAPINFO*)&bih, DIB_RGB_COLORS,
        (void**)&temp_bits, NULL, 0);

    if ((GetDeviceCaps(graphics->hdc, TECHNOLOGY) == DT_RASPRINTER &&
         GetDeviceCaps(graphics->hdc, SHADEBLENDCAPS) == SB_NONE) ||
            fmt & PixelFormatPAlpha)
        memcpy(temp_bits, src, src_width * src_height * 4);
    else
        convert_32bppARGB_to_32bppPARGB(src_width, src_height, temp_bits,
                                        4 * src_width, src, src_stride);

    SelectObject(hdc, hbitmap);
    gdi_alpha_blend(graphics, dst_x, dst_y, src_width, src_height,
                    hdc, 0, 0, src_width, src_height);
    DeleteDC(hdc);
    DeleteObject(hbitmap);

    return Ok;
}