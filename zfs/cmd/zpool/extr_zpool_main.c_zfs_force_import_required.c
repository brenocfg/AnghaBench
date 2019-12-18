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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ mmp_state_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ MMP_STATE_INACTIVE ; 
 scalar_t__ POOL_STATE_EXPORTED ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_HOSTID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOAD_INFO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_MMP_STATE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_STATE ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fnvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ get_system_hostid () ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static boolean_t
zfs_force_import_required(nvlist_t *config)
{
	uint64_t state;
	uint64_t hostid = 0;
	nvlist_t *nvinfo;

	state = fnvlist_lookup_uint64(config, ZPOOL_CONFIG_POOL_STATE);
	(void) nvlist_lookup_uint64(config, ZPOOL_CONFIG_HOSTID, &hostid);

	if (state != POOL_STATE_EXPORTED && hostid != get_system_hostid())
		return (B_TRUE);

	nvinfo = fnvlist_lookup_nvlist(config, ZPOOL_CONFIG_LOAD_INFO);
	if (nvlist_exists(nvinfo, ZPOOL_CONFIG_MMP_STATE)) {
		mmp_state_t mmp_state = fnvlist_lookup_uint64(nvinfo,
		    ZPOOL_CONFIG_MMP_STATE);

		if (mmp_state != MMP_STATE_INACTIVE)
			return (B_TRUE);
	}

	return (B_FALSE);
}