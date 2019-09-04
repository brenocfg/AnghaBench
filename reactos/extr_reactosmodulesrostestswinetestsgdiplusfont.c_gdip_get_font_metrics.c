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
struct font_metrics {double font_size; int /*<<< orphan*/  descent; int /*<<< orphan*/  ascent; int /*<<< orphan*/  line_spacing; int /*<<< orphan*/  em_height; scalar_t__ lfHeight; int /*<<< orphan*/  font_height; } ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpFontFamily ;
typedef  int /*<<< orphan*/  GpFont ;

/* Variables and functions */
 int /*<<< orphan*/  GdipDeleteFontFamily (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetCellAscent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetCellDescent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetEmHeight (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetFamily (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipGetFontHeight (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetFontSize (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  GdipGetFontStyle (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipGetLineSpacing (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gdip_get_font_metrics(GpFont *font, struct font_metrics *fm)
{
    INT style;
    GpFontFamily *family;
    GpStatus stat;

    stat = GdipGetFontStyle(font, &style);
    expect(Ok, stat);

    stat = GdipGetFontHeight(NULL, NULL, &fm->font_height);
    expect(InvalidParameter, stat);

    stat = GdipGetFontHeight(font, NULL, NULL);
    expect(InvalidParameter, stat);

    stat = GdipGetFontHeight(font, NULL, &fm->font_height);
    expect(Ok, stat);
    stat = GdipGetFontSize(font, &fm->font_size);
    expect(Ok, stat);

    fm->lfHeight = (INT)(fm->font_size * -1.0);

    stat = GdipGetFamily(font, &family);
    expect(Ok, stat);

    stat = GdipGetEmHeight(family, style, &fm->em_height);
    expect(Ok, stat);
    stat = GdipGetLineSpacing(family, style, &fm->line_spacing);
    expect(Ok, stat);
    stat = GdipGetCellAscent(family, style, &fm->ascent);
    expect(Ok, stat);
    stat = GdipGetCellDescent(family, style, &fm->descent);
    expect(Ok, stat);

    GdipDeleteFontFamily(family);
}