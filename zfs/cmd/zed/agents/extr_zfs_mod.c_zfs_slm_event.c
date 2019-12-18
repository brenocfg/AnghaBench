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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  zed_log_msg (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  zfs_slm_deliver_event (char const*,char const*,int /*<<< orphan*/ *) ; 

void
zfs_slm_event(const char *class, const char *subclass, nvlist_t *nvl)
{
	zed_log_msg(LOG_INFO, "zfs_slm_event: %s.%s", class, subclass);
	(void) zfs_slm_deliver_event(class, subclass, nvl);
}