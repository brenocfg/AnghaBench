#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_3__ {int month; int day; scalar_t__ time; } ;
typedef  TYPE_1__ Interval ;

/* Variables and functions */
 int DAYS_PER_MONTH ; 
 int USECS_PER_DAY ; 

int64
ts_get_interval_period_approx(Interval *interval)
{
	return interval->time + (((interval->month * DAYS_PER_MONTH) + interval->day) * USECS_PER_DAY);
}