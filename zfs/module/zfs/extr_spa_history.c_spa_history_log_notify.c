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
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESC_ZFS_HISTORY_EVENT ; 
 int /*<<< orphan*/  ZFS_EV_HIST_CMD ; 
 int /*<<< orphan*/  ZFS_EV_HIST_DSID ; 
 int /*<<< orphan*/  ZFS_EV_HIST_DSNAME ; 
 int /*<<< orphan*/  ZFS_EV_HIST_HOST ; 
 int /*<<< orphan*/  ZFS_EV_HIST_INT_EVENT ; 
 int /*<<< orphan*/  ZFS_EV_HIST_INT_NAME ; 
 int /*<<< orphan*/  ZFS_EV_HIST_INT_STR ; 
 int /*<<< orphan*/  ZFS_EV_HIST_IOCTL ; 
 int /*<<< orphan*/  ZFS_EV_HIST_TIME ; 
 int /*<<< orphan*/  ZFS_EV_HIST_TXG ; 
 int /*<<< orphan*/  ZFS_EV_HIST_WHO ; 
 int /*<<< orphan*/  ZFS_EV_HIST_ZONE ; 
 int /*<<< orphan*/  ZPOOL_HIST_CMD ; 
 int /*<<< orphan*/  ZPOOL_HIST_DSID ; 
 int /*<<< orphan*/  ZPOOL_HIST_DSNAME ; 
 int /*<<< orphan*/  ZPOOL_HIST_HOST ; 
 int /*<<< orphan*/  ZPOOL_HIST_INT_EVENT ; 
 int /*<<< orphan*/  ZPOOL_HIST_INT_NAME ; 
 int /*<<< orphan*/  ZPOOL_HIST_INT_STR ; 
 int /*<<< orphan*/  ZPOOL_HIST_IOCTL ; 
 int /*<<< orphan*/  ZPOOL_HIST_TIME ; 
 int /*<<< orphan*/  ZPOOL_HIST_TXG ; 
 int /*<<< orphan*/  ZPOOL_HIST_WHO ; 
 int /*<<< orphan*/  ZPOOL_HIST_ZONE ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_event_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_history_log_notify(spa_t *spa, nvlist_t *nvl)
{
	nvlist_t *hist_nvl = fnvlist_alloc();
	uint64_t uint64;
	char *string;

	if (nvlist_lookup_string(nvl, ZPOOL_HIST_CMD, &string) == 0)
		fnvlist_add_string(hist_nvl, ZFS_EV_HIST_CMD, string);

	if (nvlist_lookup_string(nvl, ZPOOL_HIST_INT_NAME, &string) == 0)
		fnvlist_add_string(hist_nvl, ZFS_EV_HIST_INT_NAME, string);

	if (nvlist_lookup_string(nvl, ZPOOL_HIST_ZONE, &string) == 0)
		fnvlist_add_string(hist_nvl, ZFS_EV_HIST_ZONE, string);

	if (nvlist_lookup_string(nvl, ZPOOL_HIST_HOST, &string) == 0)
		fnvlist_add_string(hist_nvl, ZFS_EV_HIST_HOST, string);

	if (nvlist_lookup_string(nvl, ZPOOL_HIST_DSNAME, &string) == 0)
		fnvlist_add_string(hist_nvl, ZFS_EV_HIST_DSNAME, string);

	if (nvlist_lookup_string(nvl, ZPOOL_HIST_INT_STR, &string) == 0)
		fnvlist_add_string(hist_nvl, ZFS_EV_HIST_INT_STR, string);

	if (nvlist_lookup_string(nvl, ZPOOL_HIST_IOCTL, &string) == 0)
		fnvlist_add_string(hist_nvl, ZFS_EV_HIST_IOCTL, string);

	if (nvlist_lookup_string(nvl, ZPOOL_HIST_INT_NAME, &string) == 0)
		fnvlist_add_string(hist_nvl, ZFS_EV_HIST_INT_NAME, string);

	if (nvlist_lookup_uint64(nvl, ZPOOL_HIST_DSID, &uint64) == 0)
		fnvlist_add_uint64(hist_nvl, ZFS_EV_HIST_DSID, uint64);

	if (nvlist_lookup_uint64(nvl, ZPOOL_HIST_TXG, &uint64) == 0)
		fnvlist_add_uint64(hist_nvl, ZFS_EV_HIST_TXG, uint64);

	if (nvlist_lookup_uint64(nvl, ZPOOL_HIST_TIME, &uint64) == 0)
		fnvlist_add_uint64(hist_nvl, ZFS_EV_HIST_TIME, uint64);

	if (nvlist_lookup_uint64(nvl, ZPOOL_HIST_WHO, &uint64) == 0)
		fnvlist_add_uint64(hist_nvl, ZFS_EV_HIST_WHO, uint64);

	if (nvlist_lookup_uint64(nvl, ZPOOL_HIST_INT_EVENT, &uint64) == 0)
		fnvlist_add_uint64(hist_nvl, ZFS_EV_HIST_INT_EVENT, uint64);

	spa_event_notify(spa, NULL, hist_nvl, ESC_ZFS_HISTORY_EVENT);

	nvlist_free(hist_nvl);
}