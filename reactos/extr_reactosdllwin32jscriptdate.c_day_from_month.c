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

__attribute__((used)) static inline int day_from_month(int month, int in_leap_year)
{
    switch(month)
    {
        case 0:
            return 0;
        case 1:
            return 31;
        case 2:
            return 59+in_leap_year;
        case 3:
            return 90+in_leap_year;
        case 4:
            return 120+in_leap_year;
        case 5:
            return 151+in_leap_year;
        case 6:
            return 181+in_leap_year;
        case 7:
            return 212+in_leap_year;
        case 8:
            return 243+in_leap_year;
        case 9:
            return 273+in_leap_year;
        case 10:
            return 304+in_leap_year;
        default:
            return 334+in_leap_year;
    }
}