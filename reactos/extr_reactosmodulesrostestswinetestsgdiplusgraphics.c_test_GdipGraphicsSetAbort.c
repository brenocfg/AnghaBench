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
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  pGdipGraphicsSetAbort (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GdipGraphicsSetAbort(void)
{
    HDC hdc;
    GpStatus status;
    GpGraphics *graphics;

    if (!pGdipGraphicsSetAbort)
    {
        win_skip("GdipGraphicsSetAbort() is not supported.\n");
        return;
    }

    hdc = GetDC(hwnd);

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    status = pGdipGraphicsSetAbort(NULL, NULL);
    expect(InvalidParameter, status);

    status = pGdipGraphicsSetAbort(graphics, NULL);
    expect(Ok, status);

    GdipDeleteGraphics(graphics);

    ReleaseDC(hwnd, hdc);
}