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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_zed_event_add_array_err(uint64_t eid, const char *name)
{
	errno = EMSGSIZE;
	zed_log_msg(LOG_WARNING,
	    "Failed to convert nvpair \"%s\" for eid=%llu: "
	    "Exceeded buffer size", name, eid);
	return (-1);
}