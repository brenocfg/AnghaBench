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
typedef  unsigned short time_t ;

/* Variables and functions */
 unsigned short* day_n ; 

__attribute__((used)) static time_t date_dos2unix(unsigned short time, unsigned short date)
{
    int month, year;
    time_t secs;

    month = ((date >> 5) & 15) - 1;
    if (month < 0) {
	/* make sure that nothing bad happens if the month bits were zero */
	month = 0;
    }
    year = date >> 9;
    secs =
	(time & 31) * 2 + 60 * ((time >> 5) & 63) + (time >> 11) * 3600 +
	86400 * ((date & 31) - 1 + day_n[month] + (year / 4) + year * 365 -
		 ((year & 3) == 0 && month < 2 ? 1 : 0) + 3653);
    /* days since 1.1.70 plus 80's leap day */
    return secs;
}