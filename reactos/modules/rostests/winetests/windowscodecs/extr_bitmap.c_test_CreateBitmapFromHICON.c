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
typedef  int /*<<< orphan*/  WICPixelFormatGUID ;
typedef  int UINT ;
struct TYPE_3__ {int fIcon; scalar_t__ hbmColor; scalar_t__ hbmMask; scalar_t__ yHotspot; scalar_t__ xHotspot; } ;
typedef  int /*<<< orphan*/  IWICBitmap ;
typedef  TYPE_1__ ICONINFO ;
typedef  int HRESULT ;
typedef  scalar_t__ HICON ;

/* Variables and functions */
 void* CreateBitmap (int,int,int,int,char const*) ; 
 scalar_t__ CreateIconIndirect (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  DestroyIcon (scalar_t__) ; 
 int /*<<< orphan*/  ERROR_INVALID_CURSOR_HANDLE ; 
 int E_INVALIDARG ; 
 int /*<<< orphan*/  GUID_WICPixelFormat32bppBGRA ; 
 int HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWICBitmap_GetPixelFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IWICBitmap_GetSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IWICBitmap_Release (int /*<<< orphan*/ *) ; 
 int IWICImagingFactory_CreateBitmapFromHICON (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **) ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  factory ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_CreateBitmapFromHICON(void)
{
    static const char bits[4096];
    HICON icon;
    ICONINFO info;
    HRESULT hr;
    IWICBitmap *bitmap;
    UINT width, height;
    WICPixelFormatGUID format;

    /* 1 bpp mask */
    info.fIcon = 1;
    info.xHotspot = 0;
    info.yHotspot = 0;
    info.hbmColor = 0;
    info.hbmMask = CreateBitmap(16, 32, 1, 1, bits);
    ok(info.hbmMask != 0, "CreateBitmap failed\n");
    icon = CreateIconIndirect(&info);
    ok(icon != 0, "CreateIconIndirect failed\n");
    DeleteObject(info.hbmMask);

    hr = IWICImagingFactory_CreateBitmapFromHICON(factory, 0, NULL);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %#x\n", hr);

    hr = IWICImagingFactory_CreateBitmapFromHICON(factory, 0, &bitmap);
    ok(hr == HRESULT_FROM_WIN32(ERROR_INVALID_CURSOR_HANDLE), "expected ERROR_INVALID_CURSOR_HANDLE, got %#x\n", hr);

    hr = IWICImagingFactory_CreateBitmapFromHICON(factory, icon, NULL);
    ok(hr == E_INVALIDARG, "expected E_INVALIDARG, got %#x\n", hr);

    hr = IWICImagingFactory_CreateBitmapFromHICON(factory, icon, &bitmap);
    ok(hr == S_OK, "CreateBitmapFromHICON error %#x\n", hr);
    DestroyIcon(icon);
    if (hr != S_OK) return;

    IWICBitmap_GetPixelFormat(bitmap, &format);
    ok(IsEqualGUID(&format, &GUID_WICPixelFormat32bppBGRA),
       "unexpected pixel format %s\n", wine_dbgstr_guid(&format));

    hr = IWICBitmap_GetSize(bitmap, &width, &height);
    ok(hr == S_OK, "IWICBitmap_GetSize error %#x\n", hr);
    ok(width == 16, "expected 16, got %u\n", width);
    ok(height == 16, "expected 16, got %u\n", height);

    IWICBitmap_Release(bitmap);

    /* 24 bpp color, 1 bpp mask */
    info.fIcon = 1;
    info.xHotspot = 0;
    info.yHotspot = 0;
    info.hbmColor = CreateBitmap(16, 16, 1, 24, bits);
    ok(info.hbmColor != 0, "CreateBitmap failed\n");
    info.hbmMask = CreateBitmap(16, 16, 1, 1, bits);
    ok(info.hbmMask != 0, "CreateBitmap failed\n");
    icon = CreateIconIndirect(&info);
    ok(icon != 0, "CreateIconIndirect failed\n");
    DeleteObject(info.hbmColor);
    DeleteObject(info.hbmMask);

    hr = IWICImagingFactory_CreateBitmapFromHICON(factory, icon, &bitmap);
    ok(hr == S_OK, "CreateBitmapFromHICON error %#x\n", hr);
    DestroyIcon(icon);

    IWICBitmap_GetPixelFormat(bitmap, &format);
    ok(IsEqualGUID(&format, &GUID_WICPixelFormat32bppBGRA),
       "unexpected pixel format %s\n", wine_dbgstr_guid(&format));

    hr = IWICBitmap_GetSize(bitmap, &width, &height);
    ok(hr == S_OK, "IWICBitmap_GetSize error %#x\n", hr);
    ok(width == 16, "expected 16, got %u\n", width);
    ok(height == 16, "expected 16, got %u\n", height);

    IWICBitmap_Release(bitmap);
}