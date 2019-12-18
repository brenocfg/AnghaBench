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
typedef  int /*<<< orphan*/  region_data ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  REAL ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  COLORREF ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetClip (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetRegionData (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGraphicsClear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GdipResetClip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipResetWorldTransform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipScaleWorldTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetClipRect (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetPixel (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MatrixOrderAppend ; 
 int Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 

__attribute__((used)) static void test_clip_xform(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    HDC hdc = GetDC( hwnd );
    GpRegion *clip;
    COLORREF color;
    UINT region_data_size;
    struct {
        DWORD size;
        DWORD checksum;
        DWORD magic;
        DWORD num_children;
        DWORD element_type;
        REAL x;
        REAL y;
        REAL width;
        REAL height;
    } region_data;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    status = GdipCreateRegion(&clip);
    expect(Ok, status);

    status = GdipGraphicsClear(graphics, 0xff000000);
    expect(Ok, status);

    status = GdipSetClipRect(graphics, 10, 10, -10, -10, CombineModeReplace);
    expect(Ok, status);
    status = GdipGetClip(graphics, clip);
    expect(Ok, status);
    status = GdipGetRegionData(clip, (BYTE*)&region_data, sizeof(region_data), &region_data_size);
    expect(Ok, status);
    expect(36, region_data_size);
    expect(28, region_data.size);
    expect(0, region_data.num_children);
    expect(0x10000000 /* RegionDataRect */, region_data.element_type);
    expectf(0.0, region_data.x);
    expectf(0.0, region_data.y);
    expectf(10.0, region_data.width);
    expectf(10.0, region_data.height);

    /* No effect with negative width/height */
    status = GdipGraphicsClear(graphics, 0xffff0000);
    expect(Ok, status);
    color = GetPixel(hdc, 5, 5);
    expect(0, color);

    status = GdipScaleWorldTransform(graphics, 2.0, 2.0, MatrixOrderAppend);
    expect(Ok, status);

    status = GdipGraphicsClear(graphics, 0xffff0000);
    expect(Ok, status);
    color = GetPixel(hdc, 5, 5);
    expect(0, color);

    status = GdipResetClip(graphics);
    expect(Ok, status);
    status = GdipResetWorldTransform(graphics);
    expect(Ok, status);
    status = GdipGraphicsClear(graphics, 0xff000000);
    expect(Ok, status);

    status = GdipScaleWorldTransform(graphics, 2.0, 2.0, MatrixOrderAppend);
    expect(Ok, status);

    status = GdipSetClipRect(graphics, 5, 5, -5, -5, CombineModeReplace);
    expect(Ok, status);
    status = GdipGetClip(graphics, clip);
    expect(Ok, status);
    status = GdipGetRegionData(clip, (BYTE*)&region_data, sizeof(region_data), &region_data_size);
    expect(Ok, status);
    expect(36, region_data_size);
    expect(28, region_data.size);
    expect(0, region_data.num_children);
    expect(0x10000000 /* RegionDataRect */, region_data.element_type);
    expectf(0.0, region_data.x);
    expectf(0.0, region_data.y);
    expectf(5.0, region_data.width);
    expectf(5.0, region_data.height);

    status = GdipGraphicsClear(graphics, 0xffff0000);
    expect(Ok, status);
    color = GetPixel(hdc, 5, 5);
    expect(0xff, color);

    GdipDeleteGraphics(graphics);
    GdipDeleteRegion(clip);
    ReleaseDC(hwnd, hdc);
}