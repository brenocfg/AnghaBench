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
struct TYPE_4__ {int /*<<< orphan*/  IWICBitmapSource_iface; } ;
typedef  int /*<<< orphan*/  IWICFormatConverter ;
typedef  int /*<<< orphan*/  IWICBitmapSource ;
typedef  scalar_t__ HRESULT ;
typedef  TYPE_1__ BitmapTestSrc ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_WICDefaultFormatConverter ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CreateTestBitmap (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  DeleteTestBitmap (TYPE_1__*) ; 
 int /*<<< orphan*/  GUID_WICPixelFormat32bppBGR ; 
 int /*<<< orphan*/  GUID_WICPixelFormat32bppBGRA ; 
 int /*<<< orphan*/  IID_IWICFormatConverter ; 
 scalar_t__ IWICFormatConverter_CanConvert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ IWICFormatConverter_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWICFormatConverter_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WICBitmapDitherTypeNone ; 
 int /*<<< orphan*/  WICBitmapPaletteTypeCustom ; 
 int /*<<< orphan*/  compare_bitmap_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ok (scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  testdata_32bppBGR ; 
 int /*<<< orphan*/  testdata_32bppBGRA ; 

__attribute__((used)) static void test_default_converter(void)
{
    BitmapTestSrc *src_obj;
    IWICFormatConverter *converter;
    BOOL can_convert = TRUE;
    HRESULT hr;

    CreateTestBitmap(&testdata_32bppBGRA, &src_obj);

    hr = CoCreateInstance(&CLSID_WICDefaultFormatConverter, NULL, CLSCTX_INPROC_SERVER,
        &IID_IWICFormatConverter, (void**)&converter);
    ok(SUCCEEDED(hr), "CoCreateInstance failed, hr=%x\n", hr);
    if (SUCCEEDED(hr))
    {
        hr = IWICFormatConverter_CanConvert(converter, &GUID_WICPixelFormat32bppBGRA,
            &GUID_WICPixelFormat32bppBGR, &can_convert);
        ok(SUCCEEDED(hr), "CanConvert returned %x\n", hr);
        ok(can_convert, "expected TRUE, got %i\n", can_convert);

        hr = IWICFormatConverter_Initialize(converter, &src_obj->IWICBitmapSource_iface,
            &GUID_WICPixelFormat32bppBGR, WICBitmapDitherTypeNone, NULL, 0.0,
            WICBitmapPaletteTypeCustom);
        ok(SUCCEEDED(hr), "Initialize returned %x\n", hr);

        if (SUCCEEDED(hr))
            compare_bitmap_data(&testdata_32bppBGRA, &testdata_32bppBGR, (IWICBitmapSource*)converter, "default converter");

        IWICFormatConverter_Release(converter);
    }

    DeleteTestBitmap(src_obj);
}