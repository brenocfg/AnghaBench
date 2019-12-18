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
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  CE_WARN ; 
 int /*<<< orphan*/  EBADF ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_HOSTID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_HOSTNAME ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* fnvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  spa_is_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_load_failed (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_name (int /*<<< orphan*/ *) ; 
 scalar_t__ zone_get_hostid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
spa_verify_host(spa_t *spa, nvlist_t *mos_config)
{
	uint64_t hostid;
	char *hostname;
	uint64_t myhostid = 0;

	if (!spa_is_root(spa) && nvlist_lookup_uint64(mos_config,
	    ZPOOL_CONFIG_HOSTID, &hostid) == 0) {
		hostname = fnvlist_lookup_string(mos_config,
		    ZPOOL_CONFIG_HOSTNAME);

		myhostid = zone_get_hostid(NULL);

		if (hostid != 0 && myhostid != 0 && hostid != myhostid) {
			cmn_err(CE_WARN, "pool '%s' could not be "
			    "loaded as it was last accessed by "
			    "another system (host: %s hostid: 0x%llx). "
			    "See: http://illumos.org/msg/ZFS-8000-EY",
			    spa_name(spa), hostname, (u_longlong_t)hostid);
			spa_load_failed(spa, "hostid verification failed: pool "
			    "last accessed by host: %s (hostid: 0x%llx)",
			    hostname, (u_longlong_t)hostid);
			return (SET_ERROR(EBADF));
		}
	}

	return (0);
}