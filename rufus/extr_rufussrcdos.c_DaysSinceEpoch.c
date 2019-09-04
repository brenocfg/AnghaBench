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
 int DAYSPERNORMALYEAR ; 
 int EPOCHYEAR ; 

__attribute__((used)) static int DaysSinceEpoch(int Year)
{
	int Days;
	Year--; /* Don't include a leap day from the current year */
	Days = Year * DAYSPERNORMALYEAR + Year / 4 - Year / 100 + Year / 400;
	Days -= (EPOCHYEAR - 1) * DAYSPERNORMALYEAR + (EPOCHYEAR - 1) / 4 - (EPOCHYEAR - 1) / 100 + (EPOCHYEAR - 1) / 400;
	return Days;
}