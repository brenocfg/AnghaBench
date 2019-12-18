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
typedef  scalar_t__ time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_isdst; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZERO (struct tm) ; 
 struct tm* gmtime (scalar_t__*) ; 
 scalar_t__ mktime (struct tm*) ; 

__attribute__((used)) static
time_t GetUTCOffset(int mon, int mday)
{
	struct tm local_tm, utc_tm, *utc_tmptr;
	time_t local_t, utc_t, utcOffset;

	ZERO(local_tm);
	ZERO(utc_tm);
	utcOffset = 0;

	local_tm.tm_year = 94;	/* Doesn't really matter. */
	local_tm.tm_mon = mon;
	local_tm.tm_mday = mday;
	local_tm.tm_hour = 12;
	local_tm.tm_isdst = -1;
	local_t = mktime(&local_tm);

	if (local_t != (time_t) -1) {
		utc_tmptr = gmtime(&local_t);
		utc_tm.tm_year = utc_tmptr->tm_year;
		utc_tm.tm_mon = utc_tmptr->tm_mon;
		utc_tm.tm_mday = utc_tmptr->tm_mday;
		utc_tm.tm_hour = utc_tmptr->tm_hour;
		utc_tm.tm_isdst = -1;
		utc_t = mktime(&utc_tm);

		if (utc_t != (time_t) -1)
			utcOffset = (local_t - utc_t);
	}
	return (utcOffset);
}