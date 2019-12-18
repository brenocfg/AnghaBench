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
typedef  int /*<<< orphan*/  StringDigitSubstitute ;
typedef  int /*<<< orphan*/  LANGID ;
typedef  int /*<<< orphan*/  GpStringFormat ;
typedef  int /*<<< orphan*/  GpStatus ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateStringFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteStringFormat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetStringFormatDigitSubstitution (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetStringFormatDigitSubstitution (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  LANG_CHINESE ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  LANG_RUSSIAN ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  SUBLANG_CHINESE_TRADITIONAL ; 
 int /*<<< orphan*/  StringDigitSubstituteNone ; 
 int /*<<< orphan*/  StringDigitSubstituteUser ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_digitsubstitution(void)
{
    GpStringFormat *format;
    GpStatus stat;
    StringDigitSubstitute digitsub;
    LANGID digitlang;

    stat = GdipCreateStringFormat(0, LANG_RUSSIAN, &format);
    expect(Ok, stat);

    /* NULL arguments */
    stat = GdipGetStringFormatDigitSubstitution(NULL, NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipGetStringFormatDigitSubstitution(format, NULL, NULL);
    expect(Ok, stat);
    stat = GdipGetStringFormatDigitSubstitution(NULL, &digitlang, NULL);
    expect(InvalidParameter, stat);
    stat = GdipGetStringFormatDigitSubstitution(NULL, NULL, &digitsub);
    expect(InvalidParameter, stat);
    stat = GdipGetStringFormatDigitSubstitution(NULL, &digitlang, &digitsub);
    expect(InvalidParameter, stat);
    stat = GdipSetStringFormatDigitSubstitution(NULL, LANG_NEUTRAL, StringDigitSubstituteNone);
    expect(InvalidParameter, stat);

    /* try to get both and one by one */
    stat = GdipGetStringFormatDigitSubstitution(format, &digitlang, &digitsub);
    expect(Ok, stat);
    expect(StringDigitSubstituteUser, digitsub);
    expect(LANG_NEUTRAL, digitlang);

    digitsub  = StringDigitSubstituteNone;
    stat = GdipGetStringFormatDigitSubstitution(format, NULL, &digitsub);
    expect(Ok, stat);
    expect(StringDigitSubstituteUser, digitsub);

    digitlang = LANG_RUSSIAN;
    stat = GdipGetStringFormatDigitSubstitution(format, &digitlang, NULL);
    expect(Ok, stat);
    expect(LANG_NEUTRAL, digitlang);

    /* set/get */
    stat = GdipSetStringFormatDigitSubstitution(format, MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL),
                                                        StringDigitSubstituteUser);
    expect(Ok, stat);
    digitsub  = StringDigitSubstituteNone;
    digitlang = LANG_RUSSIAN;
    stat = GdipGetStringFormatDigitSubstitution(format, &digitlang, &digitsub);
    expect(Ok, stat);
    expect(StringDigitSubstituteUser, digitsub);
    expect(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_TRADITIONAL), digitlang);

    stat = GdipDeleteStringFormat(format);
    expect(Ok, stat);
}