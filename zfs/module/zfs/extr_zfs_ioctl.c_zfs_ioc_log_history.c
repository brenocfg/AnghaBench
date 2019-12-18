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
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPA_VERSION_ZPOOL_HISTORY ; 
 char* fnvlist_lookup_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_history_log (int /*<<< orphan*/ *,char*) ; 
 int spa_open (char*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ *) ; 
 char* tsd_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_allow_log_key ; 

__attribute__((used)) static int
zfs_ioc_log_history(const char *unused, nvlist_t *innvl, nvlist_t *outnvl)
{
	char *message;
	spa_t *spa;
	int error;
	char *poolname;

	/*
	 * The poolname in the ioctl is not set, we get it from the TSD,
	 * which was set at the end of the last successful ioctl that allows
	 * logging.  The secpolicy func already checked that it is set.
	 * Only one log ioctl is allowed after each successful ioctl, so
	 * we clear the TSD here.
	 */
	poolname = tsd_get(zfs_allow_log_key);
	if (poolname == NULL)
		return (SET_ERROR(EINVAL));
	(void) tsd_set(zfs_allow_log_key, NULL);
	error = spa_open(poolname, &spa, FTAG);
	kmem_strfree(poolname);
	if (error != 0)
		return (error);

	message = fnvlist_lookup_string(innvl, "message");

	if (spa_version(spa) < SPA_VERSION_ZPOOL_HISTORY) {
		spa_close(spa, FTAG);
		return (SET_ERROR(ENOTSUP));
	}

	error = spa_history_log(spa, message);
	spa_close(spa, FTAG);
	return (error);
}