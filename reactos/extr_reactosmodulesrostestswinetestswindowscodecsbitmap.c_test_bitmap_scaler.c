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
typedef  int /*<<< orphan*/  pixel_format ;
typedef  int /*<<< orphan*/  WICPixelFormatGUID ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IWICPalette ;
typedef  int /*<<< orphan*/  IWICBitmapSource ;
typedef  int /*<<< orphan*/  IWICBitmapScaler ;
typedef  int /*<<< orphan*/  IWICBitmap ;
typedef  double HRESULT ;

/* Variables and functions */
 double E_INVALIDARG ; 
 int /*<<< orphan*/  GUID_WICPixelFormat24bppBGR ; 
 int /*<<< orphan*/  GUID_WICPixelFormatDontCare ; 
 double IWICBitmapScaler_CopyPalette (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double IWICBitmapScaler_GetPixelFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double IWICBitmapScaler_GetResolution (int /*<<< orphan*/ *,double*,double*) ; 
 double IWICBitmapScaler_GetSize (int /*<<< orphan*/ *,int*,int*) ; 
 double IWICBitmapScaler_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWICBitmapScaler_Release (int /*<<< orphan*/ *) ; 
 double IWICBitmap_GetResolution (int /*<<< orphan*/ *,double*,double*) ; 
 double IWICBitmap_GetSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IWICBitmap_Release (int /*<<< orphan*/ *) ; 
 double IWICImagingFactory_CreateBitmap (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 double IWICImagingFactory_CreateBitmapScaler (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 double IWICImagingFactory_CreatePalette (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWICPalette_Release (int /*<<< orphan*/ *) ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double S_OK ; 
 int /*<<< orphan*/  WICBitmapCacheOnLoad ; 
 int /*<<< orphan*/  WICBitmapInterpolationModeNearestNeighbor ; 
 double WINCODEC_ERR_NOTINITIALIZED ; 
 double WINCODEC_ERR_PALETTEUNAVAILABLE ; 
 double WINCODEC_ERR_WRONGSTATE ; 
 int /*<<< orphan*/  factory ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,double,...) ; 
 double wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_bitmap_scaler(void)
{
    WICPixelFormatGUID pixel_format;
    IWICBitmapScaler *scaler;
    IWICPalette *palette;
    double res_x, res_y;
    IWICBitmap *bitmap;
    UINT width, height;
    HRESULT hr;

    hr = IWICImagingFactory_CreateBitmap(factory, 4, 2, &GUID_WICPixelFormat24bppBGR, WICBitmapCacheOnLoad, &bitmap);
    ok(hr == S_OK, "Failed to create a bitmap, hr %#x.\n", hr);

    hr = IWICBitmap_GetSize(bitmap, &width, &height);
    ok(hr == S_OK, "Failed to get bitmap size, hr %#x.\n", hr);
    ok(width == 4, "Unexpected width %u.\n", width);
    ok(height == 2, "Unexpected height %u.\n", height);

    hr = IWICBitmap_GetResolution(bitmap, &res_x, &res_y);
    ok(hr == S_OK, "Failed to get bitmap resolution, hr %#x.\n", hr);
    ok(res_x == 0.0 && res_y == 0.0, "Unexpected resolution %f x %f.\n", res_x, res_y);

    hr = IWICImagingFactory_CreateBitmapScaler(factory, &scaler);
    ok(hr == S_OK, "Failed to create bitmap scaler, hr %#x.\n", hr);

    hr = IWICBitmapScaler_Initialize(scaler, NULL, 0, 0,
        WICBitmapInterpolationModeNearestNeighbor);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_Initialize(scaler, (IWICBitmapSource *)bitmap, 0, 0,
        WICBitmapInterpolationModeNearestNeighbor);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_GetSize(scaler, NULL, &height);
    ok(hr == WINCODEC_ERR_NOTINITIALIZED, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_GetSize(scaler, &width, NULL);
    ok(hr == WINCODEC_ERR_NOTINITIALIZED, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_GetResolution(scaler, NULL, NULL);
    ok(hr == WINCODEC_ERR_NOTINITIALIZED, "Unexpected hr %#x.\n", hr);

    res_x = 0.1;
    hr = IWICBitmapScaler_GetResolution(scaler, &res_x, NULL);
    ok(hr == WINCODEC_ERR_NOTINITIALIZED, "Unexpected hr %#x.\n", hr);
    ok(res_x == 0.1, "Unexpected resolution %f.\n", res_x);

    hr = IWICBitmapScaler_GetResolution(scaler, NULL, &res_y);
    ok(hr == WINCODEC_ERR_NOTINITIALIZED, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_GetResolution(scaler, &res_x, &res_y);
    ok(hr == WINCODEC_ERR_NOTINITIALIZED, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_GetPixelFormat(scaler, NULL);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    memset(&pixel_format, 0, sizeof(pixel_format));
    hr = IWICBitmapScaler_GetPixelFormat(scaler, &pixel_format);
    ok(hr == S_OK, "Failed to get pixel format, hr %#x.\n", hr);
    ok(IsEqualGUID(&pixel_format, &GUID_WICPixelFormatDontCare), "Unexpected pixel format %s.\n",
        wine_dbgstr_guid(&pixel_format));

    width = 123;
    height = 321;
    hr = IWICBitmapScaler_GetSize(scaler, &width, &height);
    ok(hr == WINCODEC_ERR_NOTINITIALIZED, "Unexpected hr %#x.\n", hr);
    ok(width == 123, "Unexpected width %u.\n", width);
    ok(height == 321, "Unexpected height %u.\n", height);

    hr = IWICBitmapScaler_CopyPalette(scaler, NULL);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICImagingFactory_CreatePalette(factory, &palette);
    ok(hr == S_OK, "Failed to create a palette, hr %#x.\n", hr);
    hr = IWICBitmapScaler_CopyPalette(scaler, palette);
    ok(hr == WINCODEC_ERR_PALETTEUNAVAILABLE, "Unexpected hr %#x.\n", hr);
    IWICPalette_Release(palette);

    hr = IWICBitmapScaler_Initialize(scaler, (IWICBitmapSource *)bitmap, 4, 0,
        WICBitmapInterpolationModeNearestNeighbor);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_GetSize(scaler, &width, &height);
    ok(hr == WINCODEC_ERR_NOTINITIALIZED, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_Initialize(scaler, (IWICBitmapSource *)bitmap, 0, 2,
        WICBitmapInterpolationModeNearestNeighbor);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_GetSize(scaler, &width, &height);
    ok(hr == WINCODEC_ERR_NOTINITIALIZED, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_Initialize(scaler, NULL, 8, 4,
        WICBitmapInterpolationModeNearestNeighbor);
    ok(hr == E_INVALIDARG, "Failed to initialize bitmap scaler, hr %#x.\n", hr);

    hr = IWICBitmapScaler_Initialize(scaler, (IWICBitmapSource *)bitmap, 8, 4,
        WICBitmapInterpolationModeNearestNeighbor);
    ok(hr == S_OK, "Failed to initialize bitmap scaler, hr %#x.\n", hr);

    hr = IWICBitmapScaler_Initialize(scaler, (IWICBitmapSource *)bitmap, 0, 4,
        WICBitmapInterpolationModeNearestNeighbor);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_Initialize(scaler, (IWICBitmapSource *)bitmap, 8, 0,
        WICBitmapInterpolationModeNearestNeighbor);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_Initialize(scaler, NULL, 8, 4, WICBitmapInterpolationModeNearestNeighbor);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_Initialize(scaler, (IWICBitmapSource *)bitmap, 8, 4,
        WICBitmapInterpolationModeNearestNeighbor);
    ok(hr == WINCODEC_ERR_WRONGSTATE, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_GetSize(scaler, &width, &height);
    ok(hr == S_OK, "Failed to get scaler size, hr %#x.\n", hr);
    ok(width == 8, "Unexpected width %u.\n", width);
    ok(height == 4, "Unexpected height %u.\n", height);

    hr = IWICBitmapScaler_GetSize(scaler, NULL, &height);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_GetSize(scaler, &width, NULL);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_GetSize(scaler, NULL, NULL);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICBitmapScaler_GetPixelFormat(scaler, NULL);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    memset(&pixel_format, 0, sizeof(pixel_format));
    hr = IWICBitmapScaler_GetPixelFormat(scaler, &pixel_format);
    ok(hr == S_OK, "Failed to get pixel format, hr %#x.\n", hr);
    ok(IsEqualGUID(&pixel_format, &GUID_WICPixelFormat24bppBGR), "Unexpected pixel format %s.\n",
        wine_dbgstr_guid(&pixel_format));

    hr = IWICBitmapScaler_GetResolution(scaler, NULL, NULL);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    res_x = 0.1;
    hr = IWICBitmapScaler_GetResolution(scaler, &res_x, NULL);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);
    ok(res_x == 0.1, "Unexpected resolution %f.\n", res_x);

    hr = IWICBitmapScaler_GetResolution(scaler, NULL, &res_y);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    res_x = res_y = 1.0;
    hr = IWICBitmapScaler_GetResolution(scaler, &res_x, &res_y);
    ok(hr == S_OK, "Failed to get scaler resolution, hr %#x.\n", hr);
    ok(res_x == 0.0 && res_y == 0.0, "Unexpected resolution %f x %f.\n", res_x, res_y);

    hr = IWICImagingFactory_CreatePalette(factory, &palette);
    ok(hr == S_OK, "Failed to create a palette, hr %#x.\n", hr);
    hr = IWICBitmapScaler_CopyPalette(scaler, palette);
    ok(hr == WINCODEC_ERR_PALETTEUNAVAILABLE, "Unexpected hr %#x.\n", hr);
    IWICPalette_Release(palette);

    IWICBitmapScaler_Release(scaler);

    IWICBitmap_Release(bitmap);
}