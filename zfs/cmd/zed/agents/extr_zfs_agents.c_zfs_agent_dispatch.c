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
 char* EC_ZFS ; 
 char* FM_LIST_SUSPECT_CLASS ; 
 int /*<<< orphan*/  fmd_module_hdl (char*) ; 
 int /*<<< orphan*/  fmd_module_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 
 int /*<<< orphan*/  zfs_slm_event (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zfs_agent_dispatch(const char *class, const char *subclass, nvlist_t *nvl)
{
	/*
	 * The diagnosis engine subscribes to the following events.
	 * On illumos these subscriptions reside in:
	 * 	/usr/lib/fm/fmd/plugins/zfs-diagnosis.conf
	 */
	if (strstr(class, "ereport.fs.zfs.") != NULL ||
	    strstr(class, "resource.fs.zfs.") != NULL ||
	    strcmp(class, "sysevent.fs.zfs.vdev_remove") == 0 ||
	    strcmp(class, "sysevent.fs.zfs.vdev_remove_dev") == 0 ||
	    strcmp(class, "sysevent.fs.zfs.pool_destroy") == 0) {
		fmd_module_recv(fmd_module_hdl("zfs-diagnosis"), nvl, class);
	}

	/*
	 * The retire agent subscribes to the following events.
	 * On illumos these subscriptions reside in:
	 * 	/usr/lib/fm/fmd/plugins/zfs-retire.conf
	 *
	 * NOTE: faults events come directly from our diagnosis engine
	 * and will not pass through the zfs kernel module.
	 */
	if (strcmp(class, FM_LIST_SUSPECT_CLASS) == 0 ||
	    strcmp(class, "resource.fs.zfs.removed") == 0 ||
	    strcmp(class, "resource.fs.zfs.statechange") == 0 ||
	    strcmp(class, "sysevent.fs.zfs.vdev_remove")  == 0) {
		fmd_module_recv(fmd_module_hdl("zfs-retire"), nvl, class);
	}

	/*
	 * The SLM module only consumes disk events and vdev check events
	 *
	 * NOTE: disk events come directly from disk monitor and will
	 * not pass through the zfs kernel module.
	 */
	if (strstr(class, "EC_dev_") != NULL ||
	    strcmp(class, EC_ZFS) == 0) {
		(void) zfs_slm_event(class, subclass, nvl);
	}
}