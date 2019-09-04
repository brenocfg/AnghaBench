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
typedef  int /*<<< orphan*/  color ;
typedef  int WICColor ;
typedef  int WICBitmapPaletteType ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IWICPalette ;
typedef  int /*<<< orphan*/  IWICBitmapSource ;
typedef  int /*<<< orphan*/  IWICBitmap ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int E_INVALIDARG ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GUID_WICPixelFormat24bppRGB ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICBitmap_Release (int /*<<< orphan*/ *) ; 
 int IWICImagingFactory_CreateBitmapFromMemory (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IWICImagingFactory_CreatePalette (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IWICPalette_GetColorCount (int /*<<< orphan*/ *,int*) ; 
 int IWICPalette_GetColors (int /*<<< orphan*/ *,int,int*,int*) ; 
 int IWICPalette_GetType (int /*<<< orphan*/ *,int*) ; 
 int IWICPalette_InitializeFromBitmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWICPalette_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int WICBitmapPaletteTypeCustom ; 
 int /*<<< orphan*/  factory ; 
 int /*<<< orphan*/ * init_bitmap (int*,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_palette_from_bitmap(void)
{
    HRESULT hr;
    BYTE *data;
    IWICBitmap *bitmap;
    IWICPalette *palette;
    WICBitmapPaletteType type;
    UINT width, height, stride, count, ret;
    WICColor color[257];

    data = init_bitmap(&width, &height, &stride);

    hr = IWICImagingFactory_CreateBitmapFromMemory(factory, width, height, &GUID_WICPixelFormat24bppRGB,
                                                   stride, stride * height, data, &bitmap);
    ok(hr == S_OK, "CreateBitmapFromMemory error %#x\n", hr);

    hr = IWICImagingFactory_CreatePalette(factory, &palette);
    ok(hr == S_OK, "CreatePalette error %#x\n", hr);

    hr = IWICPalette_InitializeFromBitmap(palette, (IWICBitmapSource *)bitmap, 0, FALSE);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %#x\n", hr);

    hr = IWICPalette_InitializeFromBitmap(palette, (IWICBitmapSource *)bitmap, 1, FALSE);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %#x\n", hr);

    hr = IWICPalette_InitializeFromBitmap(palette, (IWICBitmapSource *)bitmap, 257, FALSE);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %#x\n", hr);

    hr = IWICPalette_InitializeFromBitmap(palette, NULL, 16, FALSE);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %#x\n", hr);

    hr = IWICPalette_InitializeFromBitmap(palette, (IWICBitmapSource *)bitmap, 2, FALSE);
    ok(hr == S_OK, "InitializeFromBitmap error %#x\n", hr);
    count = 0;
    hr = IWICPalette_GetColorCount(palette, &count);
    ok(hr == S_OK, "GetColorCount error %#x\n", hr);
    ok(count == 2, "expected 2, got %u\n", count);

    hr = IWICPalette_InitializeFromBitmap(palette, (IWICBitmapSource *)bitmap, 2, TRUE);
    ok(hr == S_OK, "InitializeFromBitmap error %#x\n", hr);
    count = 0;
    hr = IWICPalette_GetColorCount(palette, &count);
    ok(hr == S_OK, "GetColorCount error %#x\n", hr);
    ok(count == 2, "expected 2, got %u\n", count);

    /* without trasparent color */
    hr = IWICPalette_InitializeFromBitmap(palette, (IWICBitmapSource *)bitmap, 16, FALSE);
    ok(hr == S_OK, "InitializeFromBitmap error %#x\n", hr);
    type = -1;
    hr = IWICPalette_GetType(palette, &type);
    ok(hr == S_OK, "GetType error %#x\n", hr);
    ok(type == WICBitmapPaletteTypeCustom, "expected WICBitmapPaletteTypeCustom, got %#x\n", type);
    count = 0;
    hr = IWICPalette_GetColorCount(palette, &count);
    ok(hr == S_OK, "GetColorCount error %#x\n", hr);
    ok(count == 16, "expected 16, got %u\n", count);
    memset(color, 0, sizeof(color));
    hr = IWICPalette_GetColors(palette, count, color, &ret);
    ok(hr == S_OK, "GetColors error %#x\n", hr);
    ok(ret == count, "expected %u, got %u\n", count, ret);
    ok(color[count - 1] != 0, "expected !0, got %08x\n", color[count - 1]);

    /* with trasparent color */
    hr = IWICPalette_InitializeFromBitmap(palette, (IWICBitmapSource *)bitmap, 16, TRUE);
    ok(hr == S_OK, "InitializeFromBitmap error %#x\n", hr);
    type = -1;
    hr = IWICPalette_GetType(palette, &type);
    ok(hr == S_OK, "GetType error %#x\n", hr);
    ok(type == WICBitmapPaletteTypeCustom, "expected WICBitmapPaletteTypeCustom, got %#x\n", type);
    count = 0;
    hr = IWICPalette_GetColorCount(palette, &count);
    ok(hr == S_OK, "GetColorCount error %#x\n", hr);
    ok(count == 16, "expected 16, got %u\n", count);
    memset(color, 0xff, sizeof(color));
    hr = IWICPalette_GetColors(palette, count, color, &ret);
    ok(hr == S_OK, "GetColors error %#x\n", hr);
    ok(ret == count, "expected %u, got %u\n", count, ret);
    ok(color[count - 1] == 0, "expected 0, got %08x\n", color[count - 1]);

    IWICPalette_Release(palette);
    IWICBitmap_Release(bitmap);

    HeapFree(GetProcessHeap(), 0, data);
}