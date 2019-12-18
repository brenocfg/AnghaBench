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
 int /*<<< orphan*/  Day (double) ; 
 double HourFromTime (double) ; 
 double LocalTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakeDate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakeTime (double,double,double,double) ; 
 int /*<<< orphan*/  SecFromTime (double) ; 
 int /*<<< orphan*/  UTC (int /*<<< orphan*/ ) ; 
 double js_optnumber (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_setdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_todate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 double js_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msFromTime (double) ; 

__attribute__((used)) static void Dp_setMinutes(js_State *J)
{
	double t = LocalTime(js_todate(J, 0));
	double h = HourFromTime(t);
	double m = js_tonumber(J, 1);
	double s = js_optnumber(J, 2, SecFromTime(t));
	double ms = js_optnumber(J, 3, msFromTime(t));
	js_setdate(J, 0, UTC(MakeDate(Day(t), MakeTime(h, m, s, ms))));
}