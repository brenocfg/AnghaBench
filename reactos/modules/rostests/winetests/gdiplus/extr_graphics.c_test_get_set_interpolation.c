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
typedef  int /*<<< orphan*/  InterpolationMode ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetInterpolationMode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetInterpolationMode (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ InterpolationModeBilinear ; 
 scalar_t__ InterpolationModeDefault ; 
 scalar_t__ InterpolationModeHighQuality ; 
 scalar_t__ InterpolationModeHighQualityBicubic ; 
 scalar_t__ InterpolationModeInvalid ; 
 scalar_t__ InterpolationModeLowQuality ; 
 scalar_t__ InterpolationModeNearestNeighbor ; 
 scalar_t__ InvalidParameter ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_get_set_interpolation(void)
{
    GpGraphics *graphics;
    HDC hdc = GetDC( hwnd );
    GpStatus status;
    InterpolationMode mode;

    ok(hdc != NULL, "Expected HDC to be initialized\n");
    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");

    status = GdipGetInterpolationMode(NULL, &mode);
    expect(InvalidParameter, status);

    if (0)
    {
        /* Crashes on Windows XP */
        status = GdipGetInterpolationMode(graphics, NULL);
        expect(InvalidParameter, status);
    }

    status = GdipSetInterpolationMode(NULL, InterpolationModeNearestNeighbor);
    expect(InvalidParameter, status);

    /* out of range */
    status = GdipSetInterpolationMode(graphics, InterpolationModeHighQualityBicubic+1);
    expect(InvalidParameter, status);

    status = GdipSetInterpolationMode(graphics, InterpolationModeInvalid);
    expect(InvalidParameter, status);

    status = GdipGetInterpolationMode(graphics, &mode);
    expect(Ok, status);
    expect(InterpolationModeBilinear, mode);

    status = GdipSetInterpolationMode(graphics, InterpolationModeNearestNeighbor);
    expect(Ok, status);

    status = GdipGetInterpolationMode(graphics, &mode);
    expect(Ok, status);
    expect(InterpolationModeNearestNeighbor, mode);

    status = GdipSetInterpolationMode(graphics, InterpolationModeDefault);
    expect(Ok, status);

    status = GdipGetInterpolationMode(graphics, &mode);
    expect(Ok, status);
    expect(InterpolationModeBilinear, mode);

    status = GdipSetInterpolationMode(graphics, InterpolationModeLowQuality);
    expect(Ok, status);

    status = GdipGetInterpolationMode(graphics, &mode);
    expect(Ok, status);
    expect(InterpolationModeBilinear, mode);

    status = GdipSetInterpolationMode(graphics, InterpolationModeHighQuality);
    expect(Ok, status);

    status = GdipGetInterpolationMode(graphics, &mode);
    expect(Ok, status);
    expect(InterpolationModeHighQualityBicubic, mode);

    GdipDeleteGraphics(graphics);

    ReleaseDC(hwnd, hdc);
}