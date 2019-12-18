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
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  MakeDate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakeDay (double,double,double) ; 
 double MonthFromTime (double) ; 
 int /*<<< orphan*/  TimeWithinDay (double) ; 
 double YearFromTime (double) ; 
 int /*<<< orphan*/  js_setdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double js_todate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 double js_tonumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void Dp_setUTCDate(js_State *J)
{
	double t = js_todate(J, 0);
	double y = YearFromTime(t);
	double m = MonthFromTime(t);
	double d = js_tonumber(J, 1);
	js_setdate(J, 0, MakeDate(MakeDay(y, m, d), TimeWithinDay(t)));
}