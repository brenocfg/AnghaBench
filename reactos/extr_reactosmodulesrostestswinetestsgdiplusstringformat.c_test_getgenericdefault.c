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
 int /*<<< orphan*/  GdipDeleteStringFormat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatAlign (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatDigitSubstitution (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatFlags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatHotkeyPrefix (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatLineAlign (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatTabStopCount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatTrimming (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetStringFormatFlags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipStringFormatGetGenericDefault (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  HotkeyPrefixNone ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  StringAlignmentNear ; 
 int /*<<< orphan*/  StringDigitSubstituteUser ; 
 int /*<<< orphan*/  StringFormatFlagsNoWrap ; 
 int /*<<< orphan*/  StringTrimmingCharacter ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_getgenericdefault(void)
{
    GpStringFormat *format, *format2;
    GpStatus stat;

    INT flags;
    INT n;
    StringAlignment align, line_align;
    StringTrimming trimming;
    StringDigitSubstitute digitsub;
    LANGID digitlang;
    INT tabcount;

    /* NULL arg */
    stat = GdipStringFormatGetGenericDefault(NULL);
    expect(InvalidParameter, stat);

    stat = GdipStringFormatGetGenericDefault(&format);
    expect(Ok, stat);

    stat = GdipStringFormatGetGenericDefault(&format2);
    expect(Ok, stat);
    ok(format == format2, "expected same format object\n");
    stat = GdipDeleteStringFormat(format2);
    expect(Ok, stat);

    GdipGetStringFormatFlags(format, &flags);
    GdipGetStringFormatAlign(format, &align);
    GdipGetStringFormatLineAlign(format, &line_align);
    GdipGetStringFormatHotkeyPrefix(format, &n);
    GdipGetStringFormatTrimming(format, &trimming);
    GdipGetStringFormatDigitSubstitution(format, &digitlang, &digitsub);
    GdipGetStringFormatTabStopCount(format, &tabcount);

    expect(0, flags);
    expect(HotkeyPrefixNone, n);
    expect(StringAlignmentNear, align);
    expect(StringAlignmentNear, line_align);
    expect(StringTrimmingCharacter, trimming);
    expect(StringDigitSubstituteUser, digitsub);
    expect(LANG_NEUTRAL, digitlang);
    expect(0, tabcount);

    /* Change default format parameters, release, get format object again. */
    stat = GdipSetStringFormatFlags(format, StringFormatFlagsNoWrap);
    expect(Ok, stat);

    stat = GdipGetStringFormatFlags(format, &flags);
    expect(Ok, stat);
    expect(StringFormatFlagsNoWrap, flags);

    stat = GdipDeleteStringFormat(format);
    expect(Ok, stat);

    stat = GdipStringFormatGetGenericDefault(&format);
    expect(Ok, stat);

    stat = GdipGetStringFormatFlags(format, &flags);
    expect(Ok, stat);
    expect(StringFormatFlagsNoWrap, flags);

    stat = GdipDeleteStringFormat(format);
    expect(Ok, stat);
}