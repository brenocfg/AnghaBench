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
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpSolidFill ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathLineI (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  GdipAddPathRectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateSolidFill (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFillPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipResetPath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_GdipFillPath(void)
{
    GpStatus status;
    GpGraphics *graphics;
    GpSolidFill *brush;
    GpPath *path;
    HDC hdc = GetDC(hwnd);

    ok(hdc != NULL, "Expected HDC to be initialized\n");
    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");
    status = GdipCreateSolidFill((ARGB)0xffffffff, &brush);
    expect(Ok, status);
    ok(brush != NULL, "Expected brush to be initialized\n");
    status = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, status);
    ok(path != NULL, "Expected path to be initialized\n");

    /* Empty path */
    GdipResetPath(path);
    status = GdipFillPath(graphics, (GpBrush *)brush, path);
    expect(Ok, status);

    /* Not closed path */
    GdipResetPath(path);
    status = GdipAddPathLineI(path, 0, 0, 2, 2);
    expect(Ok, status);
    status = GdipAddPathLineI(path, 2, 2, 4, 0);
    expect(Ok, status);
    status = GdipFillPath(graphics, (GpBrush *)brush, path);
    expect(Ok, status);

    /* Closed path */
    GdipResetPath(path);
    status = GdipAddPathRectangle(path, 0, 0, 4, 4);
    expect(Ok, status);
    status = GdipFillPath(graphics, (GpBrush *)brush, path);
    expect(Ok, status);

    GdipDeletePath(path);
    GdipDeleteBrush((GpBrush *)brush);
    GdipDeleteGraphics(graphics);
    ReleaseDC(hwnd, hdc);
}