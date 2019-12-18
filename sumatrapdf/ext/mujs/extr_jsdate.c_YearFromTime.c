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
 double DaysInYear (int) ; 
 double TimeFromYear (int) ; 
 int floor (double) ; 
 double msPerDay ; 

__attribute__((used)) static int YearFromTime(double t)
{
	int y = floor(t / (msPerDay * 365.2425)) + 1970;
	double t2 = TimeFromYear(y);
	if (t2 > t)
		--y;
	else if (t2 + msPerDay * DaysInYear(y) <= t)
		++y;
	return y;
}