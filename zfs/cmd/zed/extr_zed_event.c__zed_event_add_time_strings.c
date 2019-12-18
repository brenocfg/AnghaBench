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
typedef  int /*<<< orphan*/  zed_strings_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  ZEVENT_VAR_PREFIX ; 
 int /*<<< orphan*/  _zed_event_add_var (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct tm* localtime (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
_zed_event_add_time_strings(uint64_t eid, zed_strings_t *zsp, int64_t etime[])
{
	struct tm *stp;
	char buf[32];

	assert(zsp != NULL);
	assert(etime != NULL);

	_zed_event_add_var(eid, zsp, ZEVENT_VAR_PREFIX, "TIME_SECS",
	    "%lld", (long long int) etime[0]);
	_zed_event_add_var(eid, zsp, ZEVENT_VAR_PREFIX, "TIME_NSECS",
	    "%lld", (long long int) etime[1]);

	if (!(stp = localtime((const time_t *) &etime[0]))) {
		zed_log_msg(LOG_WARNING, "Failed to add %s%s for eid=%llu: %s",
		    ZEVENT_VAR_PREFIX, "TIME_STRING", eid, "localtime error");
	} else if (!strftime(buf, sizeof (buf), "%Y-%m-%d %H:%M:%S%z", stp)) {
		zed_log_msg(LOG_WARNING, "Failed to add %s%s for eid=%llu: %s",
		    ZEVENT_VAR_PREFIX, "TIME_STRING", eid, "strftime error");
	} else {
		_zed_event_add_var(eid, zsp, ZEVENT_VAR_PREFIX, "TIME_STRING",
		    "%s", buf);
	}
}