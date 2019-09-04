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
struct tm {int tm_isdst; void* tm_year; void* tm_min; void* tm_hour; void* tm_mday; void* tm_mon; } ;

/* Variables and functions */
 void* ATOI2 (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 struct tm* localtime (int*) ; 
 int mktime (struct tm*) ; 

void
stime_arg2(char *arg, int year, time_t *tvp)
{
	struct tm *t;
					/* Start with the current time. */
	if ((t = localtime(&tvp[0])) == NULL)
		err(1, "localtime");

	t->tm_mon = ATOI2(arg);		/* MMDDhhmm[yy] */
	--t->tm_mon;			/* Convert from 01-12 to 00-11 */
	t->tm_mday = ATOI2(arg);
	t->tm_hour = ATOI2(arg);
	t->tm_min = ATOI2(arg);
	if (year)
		t->tm_year = ATOI2(arg);

	t->tm_isdst = -1;		/* Figure out DST. */
	tvp[0] = tvp[1] = mktime(t);
	if (tvp[0] == -1)
		errx(1,
	"out of range or illegal time specification: MMDDhhmm[yy]");
}