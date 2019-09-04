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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  kModTimeUnknown ; 

time_t UnMDTMDate(char *dstr)
{
#ifndef HAVE_MKTIME
	return (kModTimeUnknown);
#else
	struct tm ut, *t;
	time_t mt, now;
	time_t result = kModTimeUnknown;

	if (strncmp(dstr, "19100", 5) == 0) {
		/* Server Y2K bug! */
		return (result);
	}

	(void) time(&now);
	t = localtime(&now);

	/* Copy the whole structure of the 'tm' pointed to by t, so it will
	 * also set all fields we don't specify explicitly to be the same as
	 * they were in t.  That way we copy non-standard fields such as
	 * tm_gmtoff, if it exists or not.
	 */
	ut = *t;

	/* The time we get back from the server is (should be) in UTC. */
	if (sscanf(dstr, "%04d%02d%02d%02d%02d%02d",
		&ut.tm_year,
		&ut.tm_mon,
		&ut.tm_mday,
		&ut.tm_hour,
		&ut.tm_min,
		&ut.tm_sec) == 6)
	{
		--ut.tm_mon;
		ut.tm_year -= 1900;
		mt = mktime(&ut);
		if (mt != (time_t) -1) {
			mt += GetUTCOffset(ut.tm_mon, ut.tm_mday);
			result = (time_t) mt;
		}
	}
	return result;
#endif	/* HAVE_MKTIME */
}