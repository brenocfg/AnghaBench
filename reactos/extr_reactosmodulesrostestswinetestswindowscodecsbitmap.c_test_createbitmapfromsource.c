#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int Width; int Height; scalar_t__ Y; scalar_t__ X; } ;
typedef  TYPE_1__ WICRect ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ WICPixelFormatGUID ;
typedef  int WICBitmapPaletteType ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IWICPalette ;
typedef  int /*<<< orphan*/  IWICBitmapSource ;
typedef  int /*<<< orphan*/  IWICBitmapLock ;
typedef  void IWICBitmap ;
typedef  int HRESULT ;
typedef  int BYTE ;

/* Variables and functions */
 int E_INVALIDARG ; 
 int E_NOTIMPL ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GUID_WICPixelFormat24bppBGR ; 
 int /*<<< orphan*/  GUID_WICPixelFormat4bppIndexed ; 
 int IWICBitmapLock_GetDataPointer (int /*<<< orphan*/ *,int*,int**) ; 
 int IWICBitmapLock_GetStride (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IWICBitmapLock_Release (int /*<<< orphan*/ *) ; 
 int IWICBitmap_CopyPalette (void*,int /*<<< orphan*/ *) ; 
 int IWICBitmap_CopyPixels (void*,int /*<<< orphan*/ *,int,int,int*) ; 
 int IWICBitmap_GetPixelFormat (void*,TYPE_2__*) ; 
 int IWICBitmap_GetResolution (void*,double*,double*) ; 
 int IWICBitmap_GetSize (void*,int*,int*) ; 
 int IWICBitmap_Lock (void*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IWICBitmap_Release (void*) ; 
 int IWICBitmap_SetPalette (void*,int /*<<< orphan*/ *) ; 
 int IWICBitmap_SetResolution (void*,double,double) ; 
 int IWICImagingFactory_CreateBitmap (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int IWICImagingFactory_CreateBitmapFromSource (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int IWICImagingFactory_CreateBitmapFromSourceRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,void**) ; 
 int IWICImagingFactory_CreatePalette (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IWICPalette_GetColorCount (int /*<<< orphan*/ *,int*) ; 
 int IWICPalette_GetType (int /*<<< orphan*/ *,int*) ; 
 int IWICPalette_InitializePredefined (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWICPalette_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsEqualGUID (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int) ; 
 int S_OK ; 
 int /*<<< orphan*/  WICBitmapCacheOnLoad ; 
 int /*<<< orphan*/  WICBitmapLockWrite ; 
 int /*<<< orphan*/  WICBitmapNoCache ; 
 int WICBitmapPaletteTypeFixedGray256 ; 
 int WINCODEC_ERR_PALETTEUNAVAILABLE ; 
 int /*<<< orphan*/  bitmapsource ; 
 int /*<<< orphan*/  factory ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_createbitmapfromsource(void)
{
    HRESULT hr;
    IWICBitmap *bitmap, *bitmap2;
    IWICPalette *palette;
    IWICBitmapLock *lock;
    int i;
    WICRect rc;
    const BYTE bitmap_data[27] = {
        128,128,255, 128,128,128, 128,255,128,
        128,128,128, 128,128,128, 255,255,255,
        255,128,128, 255,255,255, 255,255,255};
    BYTE returned_data[27] = {0};
    BYTE *lock_buffer=NULL;
    UINT lock_buffer_stride=0;
    UINT lock_buffer_size=0;
    WICPixelFormatGUID pixelformat = {0};
    UINT width=0, height=0;
    double dpix=10.0, dpiy=10.0;
    UINT count;
    WICBitmapPaletteType palette_type;

    hr = IWICImagingFactory_CreateBitmap(factory, 3, 3, &GUID_WICPixelFormat24bppBGR,
        WICBitmapCacheOnLoad, &bitmap);
    ok(hr == S_OK, "IWICImagingFactory_CreateBitmap failed hr=%x\n", hr);

    if (FAILED(hr))
        return;

    hr = IWICImagingFactory_CreatePalette(factory, &palette);
    ok(hr == S_OK, "IWICImagingFactory_CreatePalette failed hr=%x\n", hr);

    hr = IWICPalette_InitializePredefined(palette, WICBitmapPaletteTypeFixedGray256, FALSE);
    ok(hr == S_OK, "IWICPalette_InitializePredefined failed hr=%x\n", hr);

    hr = IWICBitmap_SetPalette(bitmap, palette);
    ok(hr == S_OK, "IWICBitmap_SetPalette failed hr=%x\n", hr);

    IWICPalette_Release(palette);

    rc.X = rc.Y = 0;
    rc.Width = 3;
    rc.Height = 3;
    hr = IWICBitmap_Lock(bitmap, &rc, WICBitmapLockWrite, &lock);
    ok(hr == S_OK, "IWICBitmap_Lock failed hr=%x\n", hr);
    if (SUCCEEDED(hr))
    {
        hr = IWICBitmapLock_GetStride(lock, &lock_buffer_stride);
        ok(hr == S_OK, "IWICBitmapLock_GetStride failed hr=%x\n", hr);
        ok(lock_buffer_stride == 12, "got %i, expected 12\n", lock_buffer_stride);

        hr = IWICBitmapLock_GetDataPointer(lock, &lock_buffer_size, &lock_buffer);
        ok(hr == S_OK, "IWICBitmapLock_GetDataPointer failed hr=%x\n", hr);
        ok(lock_buffer_size == 33, "got %i, expected 33\n", lock_buffer_size);
        ok(lock_buffer != NULL, "got NULL data pointer\n");

        for (i=0; i<3; i++)
            memcpy(lock_buffer + lock_buffer_stride*i, bitmap_data + i*9, 9);

        IWICBitmapLock_Release(lock);
    }

    hr = IWICBitmap_SetResolution(bitmap, 12.0, 34.0);
    ok(hr == S_OK, "IWICBitmap_SetResolution failed hr=%x\n", hr);

    /* WICBitmapNoCache */
    hr = IWICImagingFactory_CreateBitmapFromSource(factory, (IWICBitmapSource *)bitmap,
        WICBitmapNoCache, &bitmap2);
    ok(hr == S_OK, "IWICImagingFactory_CreateBitmapFromSource failed hr=%x\n", hr);
    ok(bitmap2 == bitmap, "Unexpected bitmap instance.\n");

    IWICBitmap_Release(bitmap2);

    bitmap2 = (void *)0xdeadbeef;
    hr = IWICImagingFactory_CreateBitmapFromSource(factory, &bitmapsource, WICBitmapNoCache, &bitmap2);
    ok(hr == E_NOTIMPL, "Unexpected hr %#x.\n", hr);
    ok(bitmap2 == (void *)0xdeadbeef, "Unexpected pointer %p.\n", bitmap2);

    hr = IWICImagingFactory_CreateBitmapFromSource(factory, (IWICBitmapSource*)bitmap,
        WICBitmapCacheOnLoad, &bitmap2);
    ok(hr == S_OK, "IWICImagingFactory_CreateBitmapFromSource failed hr=%x\n", hr);

    IWICBitmap_Release(bitmap);

    if (FAILED(hr)) return;

    hr = IWICImagingFactory_CreatePalette(factory, &palette);
    ok(hr == S_OK, "IWICImagingFactory_CreatePalette failed hr=%x\n", hr);

    /* palette isn't copied for non-indexed formats? */
    hr = IWICBitmap_CopyPalette(bitmap2, palette);
    ok(hr == WINCODEC_ERR_PALETTEUNAVAILABLE, "IWICBitmap_CopyPalette failed hr=%x\n", hr);

    IWICPalette_Release(palette);

    hr = IWICBitmap_CopyPixels(bitmap2, NULL, 9, 27, returned_data);
    ok(hr == S_OK, "IWICBitmap_CopyPixels failed hr=%x\n", hr);

    for (i=0; i<27; i++)
        ok(returned_data[i] == bitmap_data[i], "returned_data[%i] == %i\n", i, returned_data[i]);

    hr = IWICBitmap_GetPixelFormat(bitmap2, &pixelformat);
    ok(hr == S_OK, "IWICBitmap_GetPixelFormat failed hr=%x\n", hr);
    ok(IsEqualGUID(&pixelformat, &GUID_WICPixelFormat24bppBGR), "unexpected pixel format\n");

    hr = IWICBitmap_GetResolution(bitmap2, &dpix, &dpiy);
    ok(hr == S_OK, "IWICBitmap_GetResolution failed hr=%x\n", hr);
    ok(dpix == 12.0, "got %f, expected 12.0\n", dpix);
    ok(dpiy == 34.0, "got %f, expected 34.0\n", dpiy);

    hr = IWICBitmap_GetSize(bitmap2, &width, &height);
    ok(hr == S_OK, "IWICBitmap_GetSize failed hr=%x\n", hr);
    ok(width == 3, "got %d, expected 3\n", width);
    ok(height == 3, "got %d, expected 3\n", height);

    IWICBitmap_Release(bitmap2);

    /* Ensure palette is copied for indexed formats */
    hr = IWICImagingFactory_CreateBitmap(factory, 3, 3, &GUID_WICPixelFormat4bppIndexed,
        WICBitmapCacheOnLoad, &bitmap);
    ok(hr == S_OK, "IWICImagingFactory_CreateBitmap failed hr=%x\n", hr);

    hr = IWICImagingFactory_CreatePalette(factory, &palette);
    ok(hr == S_OK, "IWICImagingFactory_CreatePalette failed hr=%x\n", hr);

    hr = IWICPalette_InitializePredefined(palette, WICBitmapPaletteTypeFixedGray256, FALSE);
    ok(hr == S_OK, "IWICPalette_InitializePredefined failed hr=%x\n", hr);

    hr = IWICBitmap_SetPalette(bitmap, palette);
    ok(hr == S_OK, "IWICBitmap_SetPalette failed hr=%x\n", hr);

    IWICPalette_Release(palette);

    hr = IWICImagingFactory_CreateBitmapFromSource(factory, (IWICBitmapSource*)bitmap,
        WICBitmapCacheOnLoad, &bitmap2);
    ok(hr == S_OK, "IWICImagingFactory_CreateBitmapFromSource failed hr=%x\n", hr);

    IWICBitmap_Release(bitmap);

    hr = IWICImagingFactory_CreatePalette(factory, &palette);
    ok(hr == S_OK, "IWICImagingFactory_CreatePalette failed hr=%x\n", hr);

    hr = IWICBitmap_CopyPalette(bitmap2, palette);
    ok(hr == S_OK, "IWICBitmap_CopyPalette failed hr=%x\n", hr);

    hr = IWICPalette_GetColorCount(palette, &count);
    ok(hr == S_OK, "IWICPalette_GetColorCount failed hr=%x\n", hr);
    ok(count == 256, "unexpected count %d\n", count);

    hr = IWICPalette_GetType(palette, &palette_type);
    ok(hr == S_OK, "IWICPalette_GetType failed hr=%x\n", hr);
    ok(palette_type == WICBitmapPaletteTypeFixedGray256, "unexpected palette type %d\n", palette_type);

    IWICPalette_Release(palette);

    hr = IWICBitmap_GetPixelFormat(bitmap2, &pixelformat);
    ok(hr == S_OK, "IWICBitmap_GetPixelFormat failed hr=%x\n", hr);
    ok(IsEqualGUID(&pixelformat, &GUID_WICPixelFormat4bppIndexed), "unexpected pixel format\n");

    hr = IWICBitmap_GetSize(bitmap2, &width, &height);
    ok(hr == S_OK, "IWICBitmap_GetSize failed hr=%x\n", hr);
    ok(width == 3, "got %d, expected 3\n", width);
    ok(height == 3, "got %d, expected 3\n", height);

    /* CreateBitmapFromSourceRect */
    hr = IWICImagingFactory_CreateBitmapFromSourceRect(factory, (IWICBitmapSource *)bitmap2, 0, 0, 16, 32, &bitmap);
    ok(hr == S_OK, "Failed to create a bitmap, hr %#x.\n", hr);
    hr = IWICBitmap_GetSize(bitmap, &width, &height);
    ok(hr == S_OK, "Failed to get bitmap size, hr %#x.\n", hr);
    ok(width == 3, "Unexpected width %u.\n", width);
    ok(height == 3, "Unexpected height %u.\n", height);
    IWICBitmap_Release(bitmap);

    hr = IWICImagingFactory_CreateBitmapFromSourceRect(factory, (IWICBitmapSource *)bitmap2, 0, 0, 1, 1, &bitmap);
    ok(hr == S_OK, "Failed to create a bitmap, hr %#x.\n", hr);
    hr = IWICBitmap_GetSize(bitmap, &width, &height);
    ok(hr == S_OK, "Failed to get bitmap size, hr %#x.\n", hr);
    ok(width == 1, "Unexpected width %u.\n", width);
    ok(height == 1, "Unexpected height %u.\n", height);
    IWICBitmap_Release(bitmap);

    hr = IWICImagingFactory_CreateBitmapFromSourceRect(factory, (IWICBitmapSource *)bitmap2, 2, 1, 16, 32, &bitmap);
    ok(hr == S_OK, "Failed to create a bitmap, hr %#x.\n", hr);
    hr = IWICBitmap_GetSize(bitmap, &width, &height);
    ok(hr == S_OK, "Failed to get bitmap size, hr %#x.\n", hr);
    ok(width == 1, "Unexpected width %u.\n", width);
    ok(height == 2, "Unexpected height %u.\n", height);
    IWICBitmap_Release(bitmap);

    hr = IWICImagingFactory_CreateBitmapFromSourceRect(factory, (IWICBitmapSource *)bitmap2, 0, 0, 0, 2, &bitmap);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICImagingFactory_CreateBitmapFromSourceRect(factory, (IWICBitmapSource *)bitmap2, 0, 0, 2, 0, &bitmap);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICImagingFactory_CreateBitmapFromSourceRect(factory, (IWICBitmapSource *)bitmap2, 1, 3, 16, 32, &bitmap);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IWICImagingFactory_CreateBitmapFromSourceRect(factory, (IWICBitmapSource *)bitmap2, 3, 1, 16, 32, &bitmap);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    IWICBitmap_Release(bitmap2);
}