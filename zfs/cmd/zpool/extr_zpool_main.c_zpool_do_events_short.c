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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  longlong_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {scalar_t__ scripted; } ;
typedef  TYPE_1__ ev_opts_t ;

/* Variables and functions */
 int /*<<< orphan*/  FM_CLASS ; 
 int /*<<< orphan*/  FM_EREPORT_TIME ; 
 int /*<<< orphan*/  ctime_r (int /*<<< orphan*/  const*,char*) ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 scalar_t__ nvlist_lookup_int64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__**,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  verify (int) ; 

__attribute__((used)) static void
zpool_do_events_short(nvlist_t *nvl, ev_opts_t *opts)
{
	char ctime_str[26], str[32], *ptr;
	int64_t *tv;
	uint_t n;

	verify(nvlist_lookup_int64_array(nvl, FM_EREPORT_TIME, &tv, &n) == 0);
	memset(str, ' ', 32);
	(void) ctime_r((const time_t *)&tv[0], ctime_str);
	(void) strncpy(str, ctime_str+4,  6);		/* 'Jun 30' */
	(void) strncpy(str+7, ctime_str+20, 4);		/* '1993' */
	(void) strncpy(str+12, ctime_str+11, 8);	/* '21:49:08' */
	(void) sprintf(str+20, ".%09lld", (longlong_t)tv[1]); /* '.123456789' */
	if (opts->scripted)
		(void) printf(gettext("%s\t"), str);
	else
		(void) printf(gettext("%s "), str);

	verify(nvlist_lookup_string(nvl, FM_CLASS, &ptr) == 0);
	(void) printf(gettext("%s\n"), ptr);
}