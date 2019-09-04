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
typedef  int /*<<< orphan*/  initcolors ;
typedef  int /*<<< orphan*/  colors ;
typedef  int WICColor ;
typedef  int WICBitmapPaletteType ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IWICPalette ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int E_INVALIDARG ; 
 int IWICImagingFactory_CreatePalette (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IWICPalette_GetColorCount (int /*<<< orphan*/ *,int*) ; 
 int IWICPalette_GetColors (int /*<<< orphan*/ *,int,int*,int*) ; 
 int IWICPalette_GetType (int /*<<< orphan*/ *,int*) ; 
 int IWICPalette_HasAlpha (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IWICPalette_InitializeCustom (int /*<<< orphan*/ *,int*,int) ; 
 int IWICPalette_InitializeFromPalette (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IWICPalette_IsBlackWhite (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IWICPalette_IsGrayscale (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IWICPalette_Release (int /*<<< orphan*/ *) ; 
 int SUCCEEDED (int) ; 
 int WICBitmapPaletteTypeCustom ; 
 int /*<<< orphan*/  factory ; 
 int /*<<< orphan*/  memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_custom_palette(void)
{
    IWICPalette *palette, *palette2;
    HRESULT hr;
    WICBitmapPaletteType type=0xffffffff;
    UINT count=1;
    const WICColor initcolors[4]={0xff000000,0xff0000ff,0xffffff00,0xffffffff};
    WICColor colors[4];
    BOOL boolresult;

    hr = IWICImagingFactory_CreatePalette(factory, &palette);
    ok(SUCCEEDED(hr), "CreatePalette failed, hr=%x\n", hr);
    if (SUCCEEDED(hr))
    {
        hr = IWICPalette_GetType(palette, &type);
        ok(SUCCEEDED(hr), "GetType failed, hr=%x\n", hr);
        ok(type == WICBitmapPaletteTypeCustom, "expected WICBitmapPaletteTypeCustom, got %x\n", type);

        hr = IWICPalette_GetColorCount(palette, &count);
        ok(SUCCEEDED(hr), "GetColorCount failed, hr=%x\n", hr);
        ok(count == 0, "expected 0, got %u\n", count);

        hr = IWICPalette_GetColors(palette, 0, colors, &count);
        ok(SUCCEEDED(hr), "GetColors failed, hr=%x\n", hr);
        ok(count == 0, "expected 0, got %u\n", count);

        hr = IWICPalette_GetColors(palette, 4, colors, &count);
        ok(SUCCEEDED(hr), "GetColors failed, hr=%x\n", hr);
        ok(count == 0, "expected 0, got %u\n", count);

        memcpy(colors, initcolors, sizeof(initcolors));
        hr = IWICPalette_InitializeCustom(palette, colors, 4);
        ok(SUCCEEDED(hr), "InitializeCustom failed, hr=%x\n", hr);

        hr = IWICPalette_GetType(palette, &type);
        ok(SUCCEEDED(hr), "GetType failed, hr=%x\n", hr);
        ok(type == WICBitmapPaletteTypeCustom, "expected WICBitmapPaletteTypeCustom, got %x\n", type);

        hr = IWICPalette_GetColorCount(palette, &count);
        ok(SUCCEEDED(hr), "GetColorCount failed, hr=%x\n", hr);
        ok(count == 4, "expected 4, got %u\n", count);

        memset(colors, 0, sizeof(colors));
        count = 0;
        hr = IWICPalette_GetColors(palette, 4, colors, &count);
        ok(SUCCEEDED(hr), "GetColors failed, hr=%x\n", hr);
        ok(count == 4, "expected 4, got %u\n", count);
        ok(!memcmp(colors, initcolors, sizeof(colors)), "got unexpected palette data\n");

        memset(colors, 0, sizeof(colors));
        count = 0;
        hr = IWICPalette_GetColors(palette, 2, colors, &count);
        ok(SUCCEEDED(hr), "GetColors failed, hr=%x\n", hr);
        ok(count == 2, "expected 2, got %u\n", count);
        ok(!memcmp(colors, initcolors, sizeof(WICColor)*2), "got unexpected palette data\n");

        count = 0;
        hr = IWICPalette_GetColors(palette, 6, colors, &count);
        ok(SUCCEEDED(hr), "GetColors failed, hr=%x\n", hr);
        ok(count == 4, "expected 4, got %u\n", count);

        hr = IWICPalette_HasAlpha(palette, &boolresult);
        ok(SUCCEEDED(hr), "HasAlpha failed, hr=%x\n", hr);
        ok(!boolresult, "expected FALSE, got TRUE\n");

        hr = IWICPalette_IsBlackWhite(palette, &boolresult);
        ok(SUCCEEDED(hr), "IsBlackWhite failed, hr=%x\n", hr);
        ok(!boolresult, "expected FALSE, got TRUE\n");

        hr = IWICPalette_IsGrayscale(palette, &boolresult);
        ok(SUCCEEDED(hr), "IsGrayscale failed, hr=%x\n", hr);
        ok(!boolresult, "expected FALSE, got TRUE\n");

        hr = IWICImagingFactory_CreatePalette(factory, &palette2);
        ok(SUCCEEDED(hr), "CreatePalette failed, hr=%x\n", hr);

        hr = IWICPalette_InitializeFromPalette(palette2, palette);
        ok(SUCCEEDED(hr), "InitializeFromPalette failed, hr=%x\n", hr);

        type = 0xdeadbeef;
        hr = IWICPalette_GetType(palette2, &type);
        ok(SUCCEEDED(hr), "GetType failed, hr=%x\n", hr);
        ok(type == WICBitmapPaletteTypeCustom, "expected WICBitmapPaletteTypeCustom, got %x\n", type);

        count = 0xdeadbeef;
        hr = IWICPalette_GetColorCount(palette2, &count);
        ok(SUCCEEDED(hr), "GetColorCount failed, hr=%x\n", hr);
        ok(count == 4, "expected 4, got %u\n", count);

        memset(colors, 0, sizeof(colors));
        count = 0xdeadbeef;
        hr = IWICPalette_GetColors(palette2, 4, colors, &count);
        ok(SUCCEEDED(hr), "GetColors failed, hr=%x\n", hr);
        ok(count == 4, "expected 4, got %u\n", count);
        ok(!memcmp(colors, initcolors, sizeof(colors)), "got unexpected palette data\n");

        /* try a palette with some alpha in it */
        colors[2] = 0x80ffffff;
        hr = IWICPalette_InitializeCustom(palette, colors, 4);
        ok(SUCCEEDED(hr), "InitializeCustom failed, hr=%x\n", hr);

        hr = IWICPalette_HasAlpha(palette, &boolresult);
        ok(SUCCEEDED(hr), "HasAlpha failed, hr=%x\n", hr);
        ok(boolresult, "expected TRUE, got FALSE\n");

        /* setting to a 0-color palette is acceptable */
        hr = IWICPalette_InitializeCustom(palette, NULL, 0);
        ok(SUCCEEDED(hr), "InitializeCustom failed, hr=%x\n", hr);

        type = 0xdeadbeef;
        hr = IWICPalette_GetType(palette, &type);
        ok(SUCCEEDED(hr), "GetType failed, hr=%x\n", hr);
        ok(type == WICBitmapPaletteTypeCustom, "expected WICBitmapPaletteTypeCustom, got %x\n", type);

        count = 0xdeadbeef;
        hr = IWICPalette_GetColorCount(palette, &count);
        ok(SUCCEEDED(hr), "GetColorCount failed, hr=%x\n", hr);
        ok(count == 0, "expected 0, got %u\n", count);

        count = 0xdeadbeef;
        hr = IWICPalette_GetColors(palette, 4, colors, &count);
        ok(SUCCEEDED(hr), "GetColors failed, hr=%x\n", hr);
        ok(count == 0, "expected 0, got %u\n", count);

        hr = IWICPalette_InitializeFromPalette(palette2, palette);
        ok(SUCCEEDED(hr), "InitializeFromPalette failed, hr=%x\n", hr);

        type = 0xdeadbeef;
        hr = IWICPalette_GetType(palette2, &type);
        ok(SUCCEEDED(hr), "GetType failed, hr=%x\n", hr);
        ok(type == WICBitmapPaletteTypeCustom, "expected WICBitmapPaletteTypeCustom, got %x\n", type);

        count = 0xdeadbeef;
        hr = IWICPalette_GetColorCount(palette2, &count);
        ok(SUCCEEDED(hr), "GetColorCount failed, hr=%x\n", hr);
        ok(count == 0, "expected 0, got %u\n", count);

        memset(colors, 0, sizeof(colors));
        count = 0xdeadbeef;
        hr = IWICPalette_GetColors(palette2, 4, colors, &count);
        ok(SUCCEEDED(hr), "GetColors failed, hr=%x\n", hr);
        ok(count == 0, "expected 0, got %u\n", count);

        /* IWICPalette is paranoid about NULL pointers */
        hr = IWICPalette_GetType(palette, NULL);
        ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %x\n", hr);

        hr = IWICPalette_GetColorCount(palette, NULL);
        ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %x\n", hr);

        hr = IWICPalette_InitializeCustom(palette, NULL, 4);
        ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %x\n", hr);

        hr = IWICPalette_GetColors(palette, 4, NULL, &count);
        ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %x\n", hr);

        hr = IWICPalette_GetColors(palette, 4, colors, NULL);
        ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %x\n", hr);

        hr = IWICPalette_HasAlpha(palette, NULL);
        ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %x\n", hr);

        hr = IWICPalette_IsBlackWhite(palette, NULL);
        ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %x\n", hr);

        hr = IWICPalette_IsGrayscale(palette, NULL);
        ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %x\n", hr);

        hr = IWICPalette_InitializeFromPalette(palette, NULL);
        ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %x\n", hr);

        IWICPalette_Release(palette2);
        IWICPalette_Release(palette);
    }
}