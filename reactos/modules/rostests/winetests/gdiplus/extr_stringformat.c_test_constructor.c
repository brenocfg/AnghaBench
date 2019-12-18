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
typedef  int /*<<< orphan*/  StringTrimming ;
typedef  int /*<<< orphan*/  StringDigitSubstitute ;
typedef  int /*<<< orphan*/  StringAlignment ;
typedef  int /*<<< orphan*/  LANGID ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  GpStringFormat ;
typedef  int /*<<< orphan*/  GpStatus ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateStringFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteStringFormat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatAlign (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatDigitSubstitution (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatHotkeyPrefix (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatLineAlign (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatMeasurableCharacterRangeCount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatTrimming (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HotkeyPrefixNone ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  StringAlignmentNear ; 
 int /*<<< orphan*/  StringDigitSubstituteUser ; 
 int /*<<< orphan*/  StringTrimmingCharacter ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_constructor(void)
{
    GpStringFormat *format;
    GpStatus stat;
    INT n, count;
    StringAlignment align, line_align;
    StringTrimming trimming;
    StringDigitSubstitute digitsub;
    LANGID digitlang;

    stat = GdipCreateStringFormat(0, LANG_NEUTRAL, &format);
    expect(Ok, stat);

    GdipGetStringFormatAlign(format, &align);
    GdipGetStringFormatLineAlign(format, &line_align);
    GdipGetStringFormatHotkeyPrefix(format, &n);
    GdipGetStringFormatTrimming(format, &trimming);
    GdipGetStringFormatDigitSubstitution(format, &digitlang, &digitsub);
    GdipGetStringFormatMeasurableCharacterRangeCount(format, &count);

    expect(HotkeyPrefixNone, n);
    expect(StringAlignmentNear, align);
    expect(StringAlignmentNear, line_align);
    expect(StringTrimmingCharacter, trimming);
    expect(StringDigitSubstituteUser, digitsub);
    expect(LANG_NEUTRAL, digitlang);
    expect(0, count);

    stat = GdipDeleteStringFormat(format);
    expect(Ok, stat);
}