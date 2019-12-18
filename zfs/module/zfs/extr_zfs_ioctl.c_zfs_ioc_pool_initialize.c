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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ POOL_INITIALIZE_CANCEL ; 
 scalar_t__ POOL_INITIALIZE_START ; 
 scalar_t__ POOL_INITIALIZE_SUSPEND ; 
 int SET_ERROR (int) ; 
 int /*<<< orphan*/  ZPOOL_INITIALIZE_COMMAND ; 
 int /*<<< orphan*/  ZPOOL_INITIALIZE_VDEVS ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ fnvlist_size (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_uint64 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_open (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int spa_vdev_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_ioc_pool_initialize(const char *poolname, nvlist_t *innvl, nvlist_t *outnvl)
{
	uint64_t cmd_type;
	if (nvlist_lookup_uint64(innvl, ZPOOL_INITIALIZE_COMMAND,
	    &cmd_type) != 0) {
		return (SET_ERROR(EINVAL));
	}

	if (!(cmd_type == POOL_INITIALIZE_CANCEL ||
	    cmd_type == POOL_INITIALIZE_START ||
	    cmd_type == POOL_INITIALIZE_SUSPEND)) {
		return (SET_ERROR(EINVAL));
	}

	nvlist_t *vdev_guids;
	if (nvlist_lookup_nvlist(innvl, ZPOOL_INITIALIZE_VDEVS,
	    &vdev_guids) != 0) {
		return (SET_ERROR(EINVAL));
	}

	for (nvpair_t *pair = nvlist_next_nvpair(vdev_guids, NULL);
	    pair != NULL; pair = nvlist_next_nvpair(vdev_guids, pair)) {
		uint64_t vdev_guid;
		if (nvpair_value_uint64(pair, &vdev_guid) != 0) {
			return (SET_ERROR(EINVAL));
		}
	}

	spa_t *spa;
	int error = spa_open(poolname, &spa, FTAG);
	if (error != 0)
		return (error);

	nvlist_t *vdev_errlist = fnvlist_alloc();
	int total_errors = spa_vdev_initialize(spa, vdev_guids, cmd_type,
	    vdev_errlist);

	if (fnvlist_size(vdev_errlist) > 0) {
		fnvlist_add_nvlist(outnvl, ZPOOL_INITIALIZE_VDEVS,
		    vdev_errlist);
	}
	fnvlist_free(vdev_errlist);

	spa_close(spa, FTAG);
	return (total_errors > 0 ? EINVAL : 0);
}