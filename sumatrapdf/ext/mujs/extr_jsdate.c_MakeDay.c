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
 size_t InLeapYear (double) ; 
 double NAN ; 
 double TimeFromYear (double) ; 
 double floor (double) ; 
 double msPerDay ; 
 double pmod (double,int) ; 

__attribute__((used)) static double MakeDay(double y, double m, double date)
{
	/*
	 * The following array contains the day of year for the first day of
	 * each month, where index 0 is January, and day 0 is January 1.
	 */
	static const double firstDayOfMonth[2][12] = {
		{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
		{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}
	};

	double yd, md;
	int im;

	y += floor(m / 12);
	m = pmod(m, 12);

	im = (int)m;
	if (im < 0 || im >= 12)
		return NAN;

	yd = floor(TimeFromYear(y) / msPerDay);
	md = firstDayOfMonth[InLeapYear(y)][im];

	return yd + md + date - 1;
}