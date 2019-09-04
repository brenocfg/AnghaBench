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
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  GpStringFormat ;
typedef  int /*<<< orphan*/  GpStatus ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateStringFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteStringFormat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatFlags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetStringFormatFlags (int /*<<< orphan*/ *,int) ; 
 int InvalidParameter ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int Ok ; 
 int StringFormatFlagsDirectionRightToLeft ; 
 int StringFormatFlagsDirectionVertical ; 
 int StringFormatFlagsDisplayFormatControl ; 
 int StringFormatFlagsMeasureTrailingSpaces ; 
 int StringFormatFlagsNoFitBlackBox ; 
 int StringFormatFlagsNoFontFallback ; 
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_stringformatflags(void)
{
    GpStringFormat *format;
    GpStatus stat;

    INT flags;

    stat = GdipCreateStringFormat(0, LANG_NEUTRAL, &format);
    expect(Ok, stat);

    /* NULL args */
    stat = GdipSetStringFormatFlags(NULL, 0);
    expect(InvalidParameter, stat);

    stat = GdipSetStringFormatFlags(format, 0);
    expect(Ok, stat);
    stat = GdipGetStringFormatFlags(format, &flags);
    expect(Ok, stat);
    expect(0, flags);

    /* Check some valid flags */
    stat = GdipSetStringFormatFlags(format, StringFormatFlagsDirectionRightToLeft);
    expect(Ok, stat);
    stat = GdipGetStringFormatFlags(format, &flags);
    expect(Ok, stat);
    expect(StringFormatFlagsDirectionRightToLeft, flags);

    stat = GdipSetStringFormatFlags(format, StringFormatFlagsNoFontFallback);
    expect(Ok, stat);
    stat = GdipGetStringFormatFlags(format, &flags);
    expect(Ok, stat);
    expect(StringFormatFlagsNoFontFallback, flags);

    /* Check some flag combinations */
    stat = GdipSetStringFormatFlags(format, StringFormatFlagsDirectionVertical
        | StringFormatFlagsNoFitBlackBox);
    expect(Ok, stat);
    stat = GdipGetStringFormatFlags(format, &flags);
    expect(Ok, stat);
    expect((StringFormatFlagsDirectionVertical
        | StringFormatFlagsNoFitBlackBox), flags);

    stat = GdipSetStringFormatFlags(format, StringFormatFlagsDisplayFormatControl
        | StringFormatFlagsMeasureTrailingSpaces);
    expect(Ok, stat);
    stat = GdipGetStringFormatFlags(format, &flags);
    expect(Ok, stat);
    expect((StringFormatFlagsDisplayFormatControl
        | StringFormatFlagsMeasureTrailingSpaces), flags);

    /* Check invalid flags */
    stat = GdipSetStringFormatFlags(format, 0xdeadbeef);
    expect(Ok, stat);
    stat = GdipGetStringFormatFlags(format, &flags);
    expect(Ok, stat);
    expect(0xdeadbeef, flags);

    stat = GdipDeleteStringFormat(format);
    expect(Ok, stat);
}