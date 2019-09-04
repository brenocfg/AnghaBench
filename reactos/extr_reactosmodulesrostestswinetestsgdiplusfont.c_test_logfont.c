#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lfa2 ;
typedef  int /*<<< orphan*/  lfa ;
typedef  int Unit ;
typedef  int UINT16 ;
struct TYPE_5__ {scalar_t__ lfHeight; int lfWidth; int lfEscapement; int lfOrientation; int lfWeight; int lfItalic; int lfUnderline; int lfStrikeOut; scalar_t__ lfCharSet; int lfOutPrecision; int lfClipPrecision; int lfQuality; int lfPitchAndFamily; int /*<<< orphan*/  lfFaceName; } ;
typedef  int /*<<< orphan*/  REAL ;
typedef  TYPE_1__ LOGFONTA ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpFontFamily ;
typedef  int /*<<< orphan*/  GpFont ;

/* Variables and functions */
 scalar_t__ ANSI_CHARSET ; 
 int FontStyleItalic ; 
 int /*<<< orphan*/  FontStyleRegular ; 
 int FontStyleStrikeout ; 
 int FontStyleUnderline ; 
 int GdipCreateFontFromLogfontA (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteFont (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteFontFamily (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int GdipGetEmHeight (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int GdipGetFamily (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipGetFontHeight (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipGetFontSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipGetFontStyle (int /*<<< orphan*/ *,int*) ; 
 int GdipGetFontUnit (int /*<<< orphan*/ *,int*) ; 
 int GdipGetLineSpacing (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int GdipGetLogFontA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ GetTextCharset (int /*<<< orphan*/ ) ; 
 int Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int UnitWorld ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expectf (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_logfont(void)
{
    LOGFONTA lfa, lfa2;
    GpFont *font;
    GpFontFamily *family;
    GpStatus stat;
    GpGraphics *graphics;
    HDC hdc = GetDC(0);
    INT style;
    REAL rval;
    UINT16 em_height, line_spacing;
    Unit unit;

    stat = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, stat);

    memset(&lfa, 0, sizeof(LOGFONTA));
    memset(&lfa2, 0xff, sizeof(LOGFONTA));
    lstrcpyA(lfa.lfFaceName, "Tahoma");

    stat = GdipCreateFontFromLogfontA(hdc, &lfa, &font);
    expect(Ok, stat);
    stat = GdipGetLogFontA(font, graphics, &lfa2);
    expect(Ok, stat);

    ok(lfa2.lfHeight < 0, "Expected negative height\n");
    expect(0, lfa2.lfWidth);
    expect(0, lfa2.lfEscapement);
    expect(0, lfa2.lfOrientation);
    ok((lfa2.lfWeight >= 100) && (lfa2.lfWeight <= 900), "Expected weight to be set\n");
    expect(0, lfa2.lfItalic);
    expect(0, lfa2.lfUnderline);
    expect(0, lfa2.lfStrikeOut);
    ok(lfa2.lfCharSet == GetTextCharset(hdc) || lfa2.lfCharSet == ANSI_CHARSET,
        "Expected %x or %x, got %x\n", GetTextCharset(hdc), ANSI_CHARSET, lfa2.lfCharSet);
    expect(0, lfa2.lfOutPrecision);
    expect(0, lfa2.lfClipPrecision);
    expect(0, lfa2.lfQuality);
    expect(0, lfa2.lfPitchAndFamily);

    GdipDeleteFont(font);

    memset(&lfa, 0, sizeof(LOGFONTA));
    lfa.lfHeight = 25;
    lfa.lfWidth = 25;
    lfa.lfEscapement = lfa.lfOrientation = 50;
    lfa.lfItalic = lfa.lfUnderline = lfa.lfStrikeOut = TRUE;

    memset(&lfa2, 0xff, sizeof(LOGFONTA));
    lstrcpyA(lfa.lfFaceName, "Tahoma");

    stat = GdipCreateFontFromLogfontA(hdc, &lfa, &font);
    expect(Ok, stat);
    stat = GdipGetLogFontA(font, graphics, &lfa2);
    expect(Ok, stat);

    ok(lfa2.lfHeight < 0, "Expected negative height\n");
    expect(0, lfa2.lfWidth);
    expect(0, lfa2.lfEscapement);
    expect(0, lfa2.lfOrientation);
    ok((lfa2.lfWeight >= 100) && (lfa2.lfWeight <= 900), "Expected weight to be set\n");
    expect(TRUE, lfa2.lfItalic);
    expect(TRUE, lfa2.lfUnderline);
    expect(TRUE, lfa2.lfStrikeOut);
    ok(lfa2.lfCharSet == GetTextCharset(hdc) || lfa2.lfCharSet == ANSI_CHARSET,
        "Expected %x or %x, got %x\n", GetTextCharset(hdc), ANSI_CHARSET, lfa2.lfCharSet);
    expect(0, lfa2.lfOutPrecision);
    expect(0, lfa2.lfClipPrecision);
    expect(0, lfa2.lfQuality);
    expect(0, lfa2.lfPitchAndFamily);

    stat = GdipGetFontStyle(font, &style);
    expect(Ok, stat);
    ok (style == (FontStyleItalic | FontStyleUnderline | FontStyleStrikeout),
            "Expected , got %d\n", style);

    stat = GdipGetFontUnit(font, &unit);
    expect(Ok, stat);
    expect(UnitWorld, unit);

    stat = GdipGetFontHeight(font, graphics, &rval);
    expect(Ok, stat);
    expectf(25.347656, rval);
    stat = GdipGetFontSize(font, &rval);
    expect(Ok, stat);
    expectf(21.0, rval);

    stat = GdipGetFamily(font, &family);
    expect(Ok, stat);
    stat = GdipGetEmHeight(family, FontStyleRegular, &em_height);
    expect(Ok, stat);
    expect(2048, em_height);
    stat = GdipGetLineSpacing(family, FontStyleRegular, &line_spacing);
    expect(Ok, stat);
    expect(2472, line_spacing);
    GdipDeleteFontFamily(family);

    GdipDeleteFont(font);

    memset(&lfa, 0, sizeof(lfa));
    lfa.lfHeight = -25;
    lstrcpyA(lfa.lfFaceName, "Tahoma");
    stat = GdipCreateFontFromLogfontA(hdc, &lfa, &font);
    expect(Ok, stat);
    memset(&lfa2, 0xff, sizeof(lfa2));
    stat = GdipGetLogFontA(font, graphics, &lfa2);
    expect(Ok, stat);
    expect(lfa.lfHeight, lfa2.lfHeight);

    stat = GdipGetFontUnit(font, &unit);
    expect(Ok, stat);
    expect(UnitWorld, unit);

    stat = GdipGetFontHeight(font, graphics, &rval);
    expect(Ok, stat);
    expectf(30.175781, rval);
    stat = GdipGetFontSize(font, &rval);
    expect(Ok, stat);
    expectf(25.0, rval);

    stat = GdipGetFamily(font, &family);
    expect(Ok, stat);
    stat = GdipGetEmHeight(family, FontStyleRegular, &em_height);
    expect(Ok, stat);
    expect(2048, em_height);
    stat = GdipGetLineSpacing(family, FontStyleRegular, &line_spacing);
    expect(Ok, stat);
    expect(2472, line_spacing);
    GdipDeleteFontFamily(family);

    GdipDeleteFont(font);

    GdipDeleteGraphics(graphics);
    ReleaseDC(0, hdc);
}