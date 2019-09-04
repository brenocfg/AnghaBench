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
typedef  char WCHAR ;
struct TYPE_5__ {double Width; } ;
typedef  TYPE_1__ RectF ;
typedef  double REAL ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int GpUnit ;
typedef  int /*<<< orphan*/  GpStringFormat ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpFontFamily ;
typedef  int /*<<< orphan*/  GpFont ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FontStyleRegular ; 
 int /*<<< orphan*/  GdipCreateFont (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateFontFamilyFromName (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateStringFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteFont (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteFontFamily (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteStringFormat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetDpiX (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  GdipGetFontSize (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  GdipMeasureString (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetPageUnit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf_ (double,double,double) ; 
 int /*<<< orphan*/  set_rect_empty (TYPE_1__*) ; 
 double units_to_pixels (double,int,double) ; 

__attribute__((used)) static void test_measured_extra_space(void)
{
    static const WCHAR tahomaW[] = { 'T','a','h','o','m','a',0 };
    static const WCHAR string[2] = { 'W','W' };
    GpStringFormat *format;
    HDC hdc;
    GpGraphics *graphics;
    GpFontFamily *family;
    GpFont *font;
    GpStatus status;
    GpUnit gfx_unit, font_unit;
    RectF bounds_1, bounds_2, rect;
    REAL margin, font_size, dpi;

    status = GdipCreateStringFormat(0, LANG_NEUTRAL, &format);
    expect(Ok, status);

    status = GdipCreateFontFamilyFromName(tahomaW, NULL, &family);
    expect(Ok, status);
    hdc = CreateCompatibleDC(0);
    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    status = GdipGetDpiX(graphics, &dpi);
    expect(Ok, status);

    /* UnitPixel = 2, UnitPoint = 3, UnitInch = 4, UnitDocument = 5, UnitMillimeter = 6 */
    /* UnitPixel as a font base unit is not tested because it differs in behaviour */
    for (font_unit = 3; font_unit <= 6; font_unit++)
    {
        status = GdipCreateFont(family, 1234.0, FontStyleRegular, font_unit, &font);
        expect(Ok, status);

        status = GdipGetFontSize(font, &font_size);
        expect(Ok, status);
        font_size = units_to_pixels(font_size, font_unit, dpi);
        /*trace("font size/6 = %f pixels\n", font_size / 6.0);*/

        /* UnitPixel = 2, UnitPoint = 3, UnitInch = 4, UnitDocument = 5, UnitMillimeter = 6 */
        for (gfx_unit = 2; gfx_unit <= 6; gfx_unit++)
        {
            status = GdipSetPageUnit(graphics, gfx_unit);
            expect(Ok, status);

            /* bounds.width of 1 glyph: [margin]+[width]+[margin] */
            set_rect_empty(&rect);
            set_rect_empty(&bounds_1);
            status = GdipMeasureString(graphics, string, 1, font, &rect, format, &bounds_1, NULL, NULL);
            expect(Ok, status);
            /* bounds.width of 2 identical glyphs: [margin]+[width]+[width]+[margin] */
            set_rect_empty(&rect);
            set_rect_empty(&bounds_2);
            status = GdipMeasureString(graphics, string, 2, font, &rect, format, &bounds_2, NULL, NULL);
            expect(Ok, status);

            /* margin = [bounds.width of 1] - [bounds.width of 2] / 2*/
            margin = units_to_pixels(bounds_1.Width - bounds_2.Width / 2.0, gfx_unit, dpi);
            /*trace("margin %f pixels\n", margin);*/
            expectf_(font_size / 6.0, margin, font_size / 100.0);
        }

        GdipDeleteFont(font);
    }

    GdipDeleteGraphics(graphics);
    DeleteDC(hdc);
    GdipDeleteFontFamily(family);
    GdipDeleteStringFormat(format);
}