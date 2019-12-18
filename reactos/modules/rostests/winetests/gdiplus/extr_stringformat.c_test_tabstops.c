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
typedef  double REAL ;
typedef  int INT ;
typedef  int /*<<< orphan*/  GpStringFormat ;
typedef  int GpStatus ;

/* Variables and functions */
 int GdipCreateStringFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int GdipDeleteStringFormat (int /*<<< orphan*/ *) ; 
 int GdipGetStringFormatTabStopCount (int /*<<< orphan*/ *,int*) ; 
 int GdipGetStringFormatTabStops (int /*<<< orphan*/ *,int,double*,double*) ; 
 int GdipSetStringFormatTabStops (int /*<<< orphan*/ *,double,int,int /*<<< orphan*/ *) ; 
 int InvalidParameter ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int NotImplemented ; 
 int Ok ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expectf (double,double) ; 
 int /*<<< orphan*/ * tabstops ; 

__attribute__((used)) static void test_tabstops(void)
{
    GpStringFormat *format;
    GpStatus stat;
    INT count;
    REAL tabs[3];
    REAL firsttab;

    stat = GdipCreateStringFormat(0, LANG_NEUTRAL, &format);
    expect(Ok, stat);

    /* NULL */
    stat = GdipGetStringFormatTabStopCount(NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipGetStringFormatTabStopCount(NULL, &count);
    expect(InvalidParameter, stat);
    stat = GdipGetStringFormatTabStopCount(format, NULL);
    expect(InvalidParameter, stat);

    stat = GdipSetStringFormatTabStops(NULL, 0.0, 0, NULL);
    expect(InvalidParameter, stat);
    stat = GdipSetStringFormatTabStops(format, 0.0, 0, NULL);
    expect(InvalidParameter, stat);
    stat = GdipSetStringFormatTabStops(NULL, 0.0, 0, tabstops);
    expect(InvalidParameter, stat);

    stat = GdipGetStringFormatTabStops(NULL, 0, NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipGetStringFormatTabStops(format, 0, NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipGetStringFormatTabStops(NULL, 0, &firsttab, NULL);
    expect(InvalidParameter, stat);
    stat = GdipGetStringFormatTabStops(NULL, 0, NULL, tabs);
    expect(InvalidParameter, stat);
    stat = GdipGetStringFormatTabStops(format, 0, &firsttab, NULL);
    expect(InvalidParameter, stat);
    stat = GdipGetStringFormatTabStops(format, 0, NULL, tabs);
    expect(InvalidParameter, stat);

    /* not NULL */
    stat = GdipGetStringFormatTabStopCount(format, &count);
    expect(Ok, stat);
    expect(0, count);
    /* negative tabcount */
    stat = GdipSetStringFormatTabStops(format, 0.0, -1, tabstops);
    expect(Ok, stat);
    count = -1;
    stat = GdipGetStringFormatTabStopCount(format, &count);
    expect(Ok, stat);
    expect(0, count);

    stat = GdipSetStringFormatTabStops(format, -10.0, 0, tabstops);
    expect(Ok, stat);
    stat = GdipSetStringFormatTabStops(format, -10.0, 1, tabstops);
    expect(NotImplemented, stat);

    firsttab = -1.0;
    tabs[0] = tabs[1] = tabs[2] = -1.0;
    stat = GdipGetStringFormatTabStops(format, 0, &firsttab, tabs);
    expect(Ok, stat);
    expectf(-1.0, tabs[0]);
    expectf(-1.0, tabs[1]);
    expectf(-1.0, tabs[2]);
    expectf(0.0, firsttab);

    stat = GdipSetStringFormatTabStops(format, +0.0, 3, tabstops);
    expect(Ok, stat);
    count = 0;
    stat = GdipGetStringFormatTabStopCount(format, &count);
    expect(Ok, stat);
    expect(3, count);

    firsttab = -1.0;
    tabs[0] = tabs[1] = tabs[2] = -1.0;
    stat = GdipGetStringFormatTabStops(format, 3, &firsttab, tabs);
    expect(Ok, stat);
    expectf(0.0,  tabs[0]);
    expectf(10.0, tabs[1]);
    expectf(2.0,  tabs[2]);
    expectf(0.0,  firsttab);

    stat = GdipSetStringFormatTabStops(format, 10.0, 3, tabstops);
    expect(Ok, stat);
    firsttab = -1.0;
    tabs[0] = tabs[1] = tabs[2] = -1.0;
    stat = GdipGetStringFormatTabStops(format, 0, &firsttab, tabs);
    expect(Ok, stat);
    expectf(-1.0, tabs[0]);
    expectf(-1.0, tabs[1]);
    expectf(-1.0, tabs[2]);
    expectf(10.0, firsttab);

    /* zero tabcount, after valid setting to 3 */
    stat = GdipSetStringFormatTabStops(format, 0.0, 0, tabstops);
    expect(Ok, stat);
    count = 0;
    stat = GdipGetStringFormatTabStopCount(format, &count);
    expect(Ok, stat);
    expect(3, count);

    stat = GdipDeleteStringFormat(format);
    expect(Ok, stat);
}