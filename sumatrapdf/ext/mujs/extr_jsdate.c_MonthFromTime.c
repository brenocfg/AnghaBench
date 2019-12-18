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

/* Variables and functions */
 int DayWithinYear (double) ; 
 int InLeapYear (double) ; 

__attribute__((used)) static int MonthFromTime(double t)
{
	int day = DayWithinYear(t);
	int leap = InLeapYear(t);
	if (day < 31) return 0;
	if (day < 59 + leap) return 1;
	if (day < 90 + leap) return 2;
	if (day < 120 + leap) return 3;
	if (day < 151 + leap) return 4;
	if (day < 181 + leap) return 5;
	if (day < 212 + leap) return 6;
	if (day < 243 + leap) return 7;
	if (day < 273 + leap) return 8;
	if (day < 304 + leap) return 9;
	if (day < 334 + leap) return 10;
	return 11;
}