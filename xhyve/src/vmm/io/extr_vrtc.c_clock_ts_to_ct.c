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
typedef  int time_t ;
struct timespec {int tv_sec; int /*<<< orphan*/  tv_nsec; } ;
struct clocktime {int year; int mon; int day; int hour; int min; int sec; int /*<<< orphan*/  nsec; int /*<<< orphan*/  dow; } ;

/* Variables and functions */
 int POSIX_BASE_YEAR ; 
 int SECDAY ; 
 int /*<<< orphan*/  day_of_week (int) ; 
 int days_in_month (int,int) ; 
 int days_in_year (int) ; 

__attribute__((used)) static void
clock_ts_to_ct(struct timespec *ts, struct clocktime *ct)
{
	int i, year, days;
	time_t rsec;	/* remainder seconds */
	time_t secs;

	secs = ts->tv_sec;
	days = (int) (secs / SECDAY);
	rsec = secs % SECDAY;

	ct->dow = day_of_week(days);

	/* Subtract out whole years, counting them in i. */
	for (year = POSIX_BASE_YEAR; days >= days_in_year(year); year++)
		days -= days_in_year(year);
	ct->year = year;

	/* Subtract out whole months, counting them in i. */
	for (i = 1; days >= days_in_month(year, i); i++)
		days -= days_in_month(year, i);
	ct->mon = i;

	/* Days are what is left over (+1) from all that. */
	ct->day = days + 1;

	/* Hours, minutes, seconds are easy */
	ct->hour = (int) (rsec / 3600);
	rsec = rsec % 3600;
	ct->min  = (int) (rsec / 60);
	rsec = rsec % 60;
	ct->sec  = (int) rsec;
	ct->nsec = ts->tv_nsec;
}