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
struct tm {size_t tm_mon; int tm_mday; int tm_year; int tm_hour; int tm_min; } ;

/* Variables and functions */
 char** gLsMon ; 
 scalar_t__ gNowMinus6Mon ; 
 scalar_t__ gNowPlus1Hr ; 
 scalar_t__ kModTimeUnknown ; 
 struct tm* localtime (scalar_t__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int,int,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void
LsDate(char *dstr, time_t ts)
{
	struct tm *gtp;

	if (ts == kModTimeUnknown) {
		(void) strcpy(dstr, "            ");
		return;
	}
	gtp = localtime(&ts);
	if (gtp == NULL) {
		(void) strcpy(dstr, "Jan  0  1900");
		return;
	}
	if ((ts > gNowPlus1Hr) || (ts < gNowMinus6Mon)) {
		(void) sprintf(dstr, "%s %2d  %4d",
			gLsMon[gtp->tm_mon],
			gtp->tm_mday,
			gtp->tm_year + 1900
		);
	} else {
		(void) sprintf(dstr, "%s %2d %02d:%02d",
			gLsMon[gtp->tm_mon],
			gtp->tm_mday,
			gtp->tm_hour,
			gtp->tm_min
		);
	}
}