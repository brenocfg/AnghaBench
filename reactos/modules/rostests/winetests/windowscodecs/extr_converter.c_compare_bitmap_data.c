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
struct bitmap_data {int width; int height; double xres; double yres; int bpp; int /*<<< orphan*/  format; } ;
struct TYPE_3__ {int Width; int Height; scalar_t__ Y; scalar_t__ X; } ;
typedef  TYPE_1__ WICRect ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IWICBitmapSource ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapSource_CopyPixels (int /*<<< orphan*/ *,TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapSource_GetPixelFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmapSource_GetResolution (int /*<<< orphan*/ *,double*,double*) ; 
 int /*<<< orphan*/  IWICBitmapSource_GetSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_bits (struct bitmap_data const*,int,int /*<<< orphan*/ *) ; 
 double fabs (double) ; 
 scalar_t__ is_indexed_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void compare_bitmap_data(const struct bitmap_data *src, const struct bitmap_data *expect,
                                IWICBitmapSource *source, const char *name)
{
    BYTE *converted_bits;
    UINT width, height;
    double xres, yres;
    WICRect prc;
    UINT stride, buffersize;
    GUID dst_pixelformat;
    HRESULT hr;

    hr = IWICBitmapSource_GetSize(source, &width, &height);
    ok(SUCCEEDED(hr), "GetSize(%s) failed, hr=%x\n", name, hr);
    ok(width == expect->width, "expecting %u, got %u (%s)\n", expect->width, width, name);
    ok(height == expect->height, "expecting %u, got %u (%s)\n", expect->height, height, name);

    hr = IWICBitmapSource_GetResolution(source, &xres, &yres);
    ok(SUCCEEDED(hr), "GetResolution(%s) failed, hr=%x\n", name, hr);
    ok(fabs(xres - expect->xres) < 0.02, "expecting %0.2f, got %0.2f (%s)\n", expect->xres, xres, name);
    ok(fabs(yres - expect->yres) < 0.02, "expecting %0.2f, got %0.2f (%s)\n", expect->yres, yres, name);

    hr = IWICBitmapSource_GetPixelFormat(source, &dst_pixelformat);
    ok(SUCCEEDED(hr), "GetPixelFormat(%s) failed, hr=%x\n", name, hr);
    ok(IsEqualGUID(&dst_pixelformat, expect->format), "got unexpected pixel format %s (%s)\n", wine_dbgstr_guid(&dst_pixelformat), name);

    prc.X = 0;
    prc.Y = 0;
    prc.Width = expect->width;
    prc.Height = expect->height;

    stride = (expect->bpp * expect->width + 7) / 8;
    buffersize = stride * expect->height;

    converted_bits = HeapAlloc(GetProcessHeap(), 0, buffersize);
    memset(converted_bits, 0xaa, buffersize);
    hr = IWICBitmapSource_CopyPixels(source, &prc, stride, buffersize, converted_bits);
    ok(SUCCEEDED(hr), "CopyPixels(%s) failed, hr=%x\n", name, hr);

    /* The result of conversion of color to indexed formats depends on
     * optimized palette generation implementation. We either need to
     * assign our own palette, or just skip the comparison.
     */
    if (!(!is_indexed_format(src->format) && is_indexed_format(expect->format)))
        ok(compare_bits(expect, buffersize, converted_bits), "unexpected pixel data (%s)\n", name);

    /* Test with NULL rectangle - should copy the whole bitmap */
    memset(converted_bits, 0xaa, buffersize);
    hr = IWICBitmapSource_CopyPixels(source, NULL, stride, buffersize, converted_bits);
    ok(SUCCEEDED(hr), "CopyPixels(%s,rc=NULL) failed, hr=%x\n", name, hr);
    /* see comment above */
    if (!(!is_indexed_format(src->format) && is_indexed_format(expect->format)))
        ok(compare_bits(expect, buffersize, converted_bits), "unexpected pixel data (%s)\n", name);

    HeapFree(GetProcessHeap(), 0, converted_bits);
}