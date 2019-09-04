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
typedef  int /*<<< orphan*/  TextRenderingHint ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetTextRenderingHint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetTextRenderingHint (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidParameter ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TextRenderingHintAntiAlias ; 
 scalar_t__ TextRenderingHintAntiAliasGridFit ; 
 scalar_t__ TextRenderingHintClearTypeGridFit ; 
 scalar_t__ TextRenderingHintSystemDefault ; 
 int /*<<< orphan*/  expect (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_get_set_textrenderinghint(void)
{
    GpGraphics *graphics;
    HDC hdc = GetDC( hwnd );
    GpStatus status;
    TextRenderingHint hint;

    ok(hdc != NULL, "Expected HDC to be initialized\n");
    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");

    status = GdipGetTextRenderingHint(NULL, &hint);
    expect(InvalidParameter, status);

    status = GdipGetTextRenderingHint(graphics, NULL);
    expect(InvalidParameter, status);

    status = GdipSetTextRenderingHint(NULL, TextRenderingHintAntiAlias);
    expect(InvalidParameter, status);

    /* out of range */
    status = GdipSetTextRenderingHint(graphics, TextRenderingHintClearTypeGridFit+1);
    expect(InvalidParameter, status);

    status = GdipGetTextRenderingHint(graphics, &hint);
    expect(Ok, status);
    expect(TextRenderingHintSystemDefault, hint);

    status = GdipSetTextRenderingHint(graphics, TextRenderingHintSystemDefault);
    expect(Ok, status);

    status = GdipGetTextRenderingHint(graphics, &hint);
    expect(Ok, status);
    expect(TextRenderingHintSystemDefault, hint);

    status = GdipSetTextRenderingHint(graphics, TextRenderingHintAntiAliasGridFit);
    expect(Ok, status);

    status = GdipGetTextRenderingHint(graphics, &hint);
    expect(Ok, status);
    expect(TextRenderingHintAntiAliasGridFit, hint);

    GdipDeleteGraphics(graphics);

    ReleaseDC(hwnd, hdc);
}