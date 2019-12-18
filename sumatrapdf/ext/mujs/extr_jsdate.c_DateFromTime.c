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
 int MonthFromTime (double) ; 

__attribute__((used)) static int DateFromTime(double t)
{
	int day = DayWithinYear(t);
	int leap = InLeapYear(t);
	switch (MonthFromTime(t)) {
	case 0: return day + 1;
	case 1: return day - 30;
	case 2: return day - 58 - leap;
	case 3: return day - 89 - leap;
	case 4: return day - 119 - leap;
	case 5: return day - 150 - leap;
	case 6: return day - 180 - leap;
	case 7: return day - 211 - leap;
	case 8: return day - 242 - leap;
	case 9: return day - 272 - leap;
	case 10: return day - 303 - leap;
	default : return day - 333 - leap;
	}
}