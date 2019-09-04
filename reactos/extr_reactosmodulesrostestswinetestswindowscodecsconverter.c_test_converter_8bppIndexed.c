#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/  IWICBitmapSource_iface; } ;
typedef  int /*<<< orphan*/  IWICPalette ;
typedef  int /*<<< orphan*/  IWICFormatConverter ;
typedef  int HRESULT ;
typedef  TYPE_1__ BitmapTestSrc ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CreateTestBitmap (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  DeleteTestBitmap (TYPE_1__*) ; 
 int E_INVALIDARG ; 
 int /*<<< orphan*/  GUID_WICPixelFormat24bppBGR ; 
 int /*<<< orphan*/  GUID_WICPixelFormat8bppIndexed ; 
 int IWICFormatConverter_CopyPalette (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IWICFormatConverter_CopyPixels (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,scalar_t__*) ; 
 int IWICFormatConverter_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWICFormatConverter_Release (int /*<<< orphan*/ *) ; 
 int IWICImagingFactory_CreateFormatConverter (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IWICImagingFactory_CreatePalette (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IWICPalette_GetColorCount (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IWICPalette_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  WICBitmapDitherTypeNone ; 
 int /*<<< orphan*/  WICBitmapPaletteTypeCustom ; 
 int /*<<< orphan*/  WICBitmapPaletteTypeFixedGray16 ; 
 int /*<<< orphan*/  WICBitmapPaletteTypeFixedHalftone64 ; 
 int /*<<< orphan*/  WICBitmapPaletteTypeMedianCut ; 
 int WINCODEC_ERR_WRONGSTATE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  factory ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  testdata_24bppBGR ; 

__attribute__((used)) static void test_converter_8bppIndexed(void)
{
    HRESULT hr;
    BitmapTestSrc *src_obj;
    IWICFormatConverter *converter;
    IWICPalette *palette;
    UINT count, i;
    BYTE buf[32 * 2 * 3]; /* enough to hold 32x2 24bppBGR data */

    CreateTestBitmap(&testdata_24bppBGR, &src_obj);

    hr = IWICImagingFactory_CreatePalette(factory, &palette);
    ok(hr == S_OK, "CreatePalette error %#x\n", hr);
    count = 0xdeadbeef;
    hr = IWICPalette_GetColorCount(palette, &count);
    ok(hr == S_OK, "GetColorCount error %#x\n", hr);
    ok(count == 0, "expected 0, got %u\n", count);

    /* NULL palette + Custom type*/
    hr = IWICImagingFactory_CreateFormatConverter(factory, &converter);
    ok(hr == S_OK, "CreateFormatConverter error %#x\n", hr);
    hr = IWICFormatConverter_Initialize(converter, &src_obj->IWICBitmapSource_iface,
                                        &GUID_WICPixelFormat24bppBGR, WICBitmapDitherTypeNone,
                                        NULL, 0.0, WICBitmapPaletteTypeCustom);
    ok(hr == S_OK, "Initialize error %#x\n", hr);
    hr = IWICFormatConverter_CopyPalette(converter, palette);
    ok(hr == 0xdeadbeef, "unexpected error %#x\n", hr);
    hr = IWICFormatConverter_CopyPixels(converter, NULL, 32 * 3, sizeof(buf), buf);
    ok(hr == S_OK, "CopyPixels error %#x\n", hr);
    IWICFormatConverter_Release(converter);

    /* NULL palette + Custom type*/
    hr = IWICImagingFactory_CreateFormatConverter(factory, &converter);
    ok(hr == S_OK, "CreateFormatConverter error %#x\n", hr);
    hr = IWICFormatConverter_Initialize(converter, &src_obj->IWICBitmapSource_iface,
                                        &GUID_WICPixelFormat8bppIndexed, WICBitmapDitherTypeNone,
                                        NULL, 0.0, WICBitmapPaletteTypeCustom);
    ok(hr == E_INVALIDARG, "unexpected error %#x\n", hr);
    hr = IWICFormatConverter_CopyPalette(converter, palette);
    ok(hr == WINCODEC_ERR_WRONGSTATE, "unexpected error %#x\n", hr);
    hr = IWICFormatConverter_CopyPixels(converter, NULL, 32, sizeof(buf), buf);
    ok(hr == WINCODEC_ERR_WRONGSTATE, "unexpected error %#x\n", hr);
    IWICFormatConverter_Release(converter);

    /* empty palette + Custom type*/
    hr = IWICImagingFactory_CreateFormatConverter(factory, &converter);
    ok(hr == S_OK, "CreateFormatConverter error %#x\n", hr);
    hr = IWICFormatConverter_Initialize(converter, &src_obj->IWICBitmapSource_iface,
                                        &GUID_WICPixelFormat8bppIndexed, WICBitmapDitherTypeNone,
                                        palette, 0.0, WICBitmapPaletteTypeCustom);
    ok(hr == S_OK, "Initialize error %#x\n", hr);
    hr = IWICFormatConverter_CopyPalette(converter, palette);
    ok(hr == S_OK, "CopyPalette error %#x\n", hr);
    count = 0xdeadbeef;
    hr = IWICPalette_GetColorCount(palette, &count);
    ok(hr == S_OK, "GetColorCount error %#x\n", hr);
    ok(count == 0, "expected 0, got %u\n", count);
    memset(buf, 0xaa, sizeof(buf));
    hr = IWICFormatConverter_CopyPixels(converter, NULL, 32, sizeof(buf), buf);
    ok(hr == S_OK, "CopyPixels error %#x\n", hr);
    count = 0;
    for (i = 0; i < 32 * 2; i++)
        if (buf[i] != 0) count++;
    ok(count == 0, "expected 0\n");
    IWICFormatConverter_Release(converter);

    /* NULL palette + Predefined type*/
    hr = IWICImagingFactory_CreateFormatConverter(factory, &converter);
    ok(hr == S_OK, "CreateFormatConverter error %#x\n", hr);
    hr = IWICFormatConverter_Initialize(converter, &src_obj->IWICBitmapSource_iface,
                                        &GUID_WICPixelFormat8bppIndexed, WICBitmapDitherTypeNone,
                                        NULL, 0.0, WICBitmapPaletteTypeFixedGray16);
    ok(hr == S_OK, "Initialize error %#x\n", hr);
    hr = IWICFormatConverter_CopyPalette(converter, palette);
    ok(hr == S_OK, "CopyPalette error %#x\n", hr);
    count = 0xdeadbeef;
    hr = IWICPalette_GetColorCount(palette, &count);
    ok(hr == S_OK, "GetColorCount error %#x\n", hr);
    ok(count == 16, "expected 16, got %u\n", count);
    hr = IWICFormatConverter_CopyPixels(converter, NULL, 32, sizeof(buf), buf);
    ok(hr == S_OK, "CopyPixels error %#x\n", hr);
    count = 0;
    for (i = 0; i < 32 * 2; i++)
        if (buf[i] != 0) count++;
    ok(count != 0, "expected != 0\n");
    IWICFormatConverter_Release(converter);

    /* not empty palette + Predefined type*/
    hr = IWICImagingFactory_CreateFormatConverter(factory, &converter);
    ok(hr == S_OK, "CreateFormatConverter error %#x\n", hr);
    hr = IWICFormatConverter_Initialize(converter, &src_obj->IWICBitmapSource_iface,
                                        &GUID_WICPixelFormat8bppIndexed, WICBitmapDitherTypeNone,
                                        palette, 0.0, WICBitmapPaletteTypeFixedHalftone64);
    ok(hr == S_OK, "Initialize error %#x\n", hr);
    hr = IWICFormatConverter_CopyPalette(converter, palette);
    ok(hr == S_OK, "CopyPalette error %#x\n", hr);
    count = 0xdeadbeef;
    hr = IWICPalette_GetColorCount(palette, &count);
    ok(hr == S_OK, "GetColorCount error %#x\n", hr);
    ok(count == 16, "expected 16, got %u\n", count);
    hr = IWICFormatConverter_CopyPixels(converter, NULL, 32, sizeof(buf), buf);
    ok(hr == S_OK, "CopyPixels error %#x\n", hr);
    count = 0;
    for (i = 0; i < 32 * 2; i++)
        if (buf[i] != 0) count++;
    ok(count != 0, "expected != 0\n");
    IWICFormatConverter_Release(converter);

    /* not empty palette + MedianCut type*/
    hr = IWICImagingFactory_CreateFormatConverter(factory, &converter);
    ok(hr == S_OK, "CreateFormatConverter error %#x\n", hr);
    hr = IWICFormatConverter_Initialize(converter, &src_obj->IWICBitmapSource_iface,
                                        &GUID_WICPixelFormat8bppIndexed, WICBitmapDitherTypeNone,
                                        palette, 0.0, WICBitmapPaletteTypeMedianCut);
    ok(hr == S_OK, "Initialize error %#x\n", hr);
    hr = IWICFormatConverter_CopyPalette(converter, palette);
    ok(hr == S_OK, "CopyPalette error %#x\n", hr);
    count = 0xdeadbeef;
    hr = IWICPalette_GetColorCount(palette, &count);
    ok(hr == S_OK, "GetColorCount error %#x\n", hr);
    ok(count == 16, "expected 16, got %u\n", count);
    hr = IWICFormatConverter_CopyPixels(converter, NULL, 32, sizeof(buf), buf);
    ok(hr == S_OK, "CopyPixels error %#x\n", hr);
    count = 0;
    for (i = 0; i < 32 * 2; i++)
        if (buf[i] != 0) count++;
    ok(count != 0, "expected != 0\n");
    IWICFormatConverter_Release(converter);

    /* NULL palette + MedianCut type*/
    hr = IWICImagingFactory_CreateFormatConverter(factory, &converter);
    ok(hr == S_OK, "CreateFormatConverter error %#x\n", hr);
    hr = IWICFormatConverter_Initialize(converter, &src_obj->IWICBitmapSource_iface,
                                        &GUID_WICPixelFormat8bppIndexed, WICBitmapDitherTypeNone,
                                        NULL, 0.0, WICBitmapPaletteTypeMedianCut);
    ok(hr == S_OK || broken(hr == E_INVALIDARG) /* XP */, "Initialize error %#x\n", hr);
    if (hr == S_OK)
    {
        hr = IWICFormatConverter_CopyPalette(converter, palette);
        ok(hr == S_OK, "CopyPalette error %#x\n", hr);
        count = 0xdeadbeef;
        hr = IWICPalette_GetColorCount(palette, &count);
        ok(hr == S_OK, "GetColorCount error %#x\n", hr);
        ok(count == 8, "expected 8, got %u\n", count);
        hr = IWICFormatConverter_CopyPixels(converter, NULL, 32, sizeof(buf), buf);
        ok(hr == S_OK, "CopyPixels error %#x\n", hr);
        count = 0;
        for (i = 0; i < 32 * 2; i++)
            if (buf[i] != 0) count++;
        ok(count != 0, "expected != 0\n");
    }
    IWICFormatConverter_Release(converter);

    IWICPalette_Release(palette);
    DeleteTestBitmap(src_obj);
}