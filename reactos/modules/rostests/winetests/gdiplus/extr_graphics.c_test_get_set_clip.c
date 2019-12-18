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
struct TYPE_3__ {double X; double Y; double Height; double Width; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateRegionRect (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetClip (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsEmptyRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsInfiniteRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipResetClip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetClipPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetClipRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 

__attribute__((used)) static void test_get_set_clip(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    HDC hdc = GetDC( hwnd );
    GpRegion *clip;
    GpRectF rect;
    BOOL res;

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    rect.X = rect.Y = 0.0;
    rect.Height = rect.Width = 100.0;

    status = GdipCreateRegionRect(&rect, &clip);
    expect(Ok, status);

    /* NULL arguments */
    status = GdipGetClip(NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipGetClip(graphics, NULL);
    expect(InvalidParameter, status);
    status = GdipGetClip(NULL, clip);
    expect(InvalidParameter, status);

    status = GdipSetClipRegion(NULL, NULL, CombineModeReplace);
    expect(InvalidParameter, status);
    status = GdipSetClipRegion(graphics, NULL, CombineModeReplace);
    expect(InvalidParameter, status);

    status = GdipSetClipPath(NULL, NULL, CombineModeReplace);
    expect(InvalidParameter, status);
    status = GdipSetClipPath(graphics, NULL, CombineModeReplace);
    expect(InvalidParameter, status);

    res = FALSE;
    status = GdipGetClip(graphics, clip);
    expect(Ok, status);
    status = GdipIsInfiniteRegion(clip, graphics, &res);
    expect(Ok, status);
    expect(TRUE, res);

    /* remains infinite after reset */
    res = FALSE;
    status = GdipResetClip(graphics);
    expect(Ok, status);
    status = GdipGetClip(graphics, clip);
    expect(Ok, status);
    status = GdipIsInfiniteRegion(clip, graphics, &res);
    expect(Ok, status);
    expect(TRUE, res);

    /* set to empty and then reset to infinite */
    status = GdipSetEmpty(clip);
    expect(Ok, status);
    status = GdipSetClipRegion(graphics, clip, CombineModeReplace);
    expect(Ok, status);

    status = GdipGetClip(graphics, clip);
    expect(Ok, status);
    res = FALSE;
    status = GdipIsEmptyRegion(clip, graphics, &res);
    expect(Ok, status);
    expect(TRUE, res);
    status = GdipResetClip(graphics);
    expect(Ok, status);
    status = GdipGetClip(graphics, clip);
    expect(Ok, status);
    res = FALSE;
    status = GdipIsInfiniteRegion(clip, graphics, &res);
    expect(Ok, status);
    expect(TRUE, res);

    GdipDeleteRegion(clip);

    GdipDeleteGraphics(graphics);
    ReleaseDC(hwnd, hdc);
}