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
typedef  int INT ;
typedef  int /*<<< orphan*/  GpStringFormat ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  CharacterRange ;

/* Variables and functions */
 int GdipCreateStringFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int GdipDeleteStringFormat (int /*<<< orphan*/ *) ; 
 int GdipGetStringFormatMeasurableCharacterRangeCount (int /*<<< orphan*/ *,int*) ; 
 int GdipSetStringFormatMeasurableCharacterRanges (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int InvalidParameter ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int Ok ; 
 int /*<<< orphan*/  expect (int,int) ; 

__attribute__((used)) static void test_characterrange(void)
{
    CharacterRange ranges[3];
    INT count;
    GpStringFormat* format;
    GpStatus stat;

    stat = GdipCreateStringFormat(0, LANG_NEUTRAL, &format);
    expect(Ok, stat);
    stat = GdipSetStringFormatMeasurableCharacterRanges(NULL, 3, ranges);
    expect(InvalidParameter, stat);
    stat = GdipSetStringFormatMeasurableCharacterRanges(format, 0, ranges);
    expect(Ok, stat);
    stat = GdipSetStringFormatMeasurableCharacterRanges(format, 3, NULL);
    expect(InvalidParameter, stat);

    stat = GdipSetStringFormatMeasurableCharacterRanges(format, 3, ranges);
    expect(Ok, stat);
    stat = GdipGetStringFormatMeasurableCharacterRangeCount(format, &count);
    expect(Ok, stat);
    if (stat == Ok) expect(3, count);

    stat= GdipDeleteStringFormat(format);
    expect(Ok, stat);
}