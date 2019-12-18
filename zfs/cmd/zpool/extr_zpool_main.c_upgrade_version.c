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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 scalar_t__ SPA_VERSION_FEATURES ; 
 int SPA_VERSION_IS_SUPPORTED (scalar_t__) ; 
 scalar_t__ ZPL_VERSION ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VERSION ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_unsupp_fs ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 char* gettext (char*) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  verify (int) ; 
 int zfs_iter_root (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_get_handle (int /*<<< orphan*/ *) ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 
 int zpool_upgrade (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
upgrade_version(zpool_handle_t *zhp, uint64_t version)
{
	int ret;
	nvlist_t *config;
	uint64_t oldversion;
	int unsupp_fs = 0;

	config = zpool_get_config(zhp, NULL);
	verify(nvlist_lookup_uint64(config, ZPOOL_CONFIG_VERSION,
	    &oldversion) == 0);

	assert(SPA_VERSION_IS_SUPPORTED(oldversion));
	assert(oldversion < version);

	ret = zfs_iter_root(zpool_get_handle(zhp), check_unsupp_fs, &unsupp_fs);
	if (ret != 0)
		return (ret);

	if (unsupp_fs) {
		(void) fprintf(stderr, gettext("Upgrade not performed due "
		    "to %d unsupported filesystems (max v%d).\n"),
		    unsupp_fs, (int)ZPL_VERSION);
		return (1);
	}

	ret = zpool_upgrade(zhp, version);
	if (ret != 0)
		return (ret);

	if (version >= SPA_VERSION_FEATURES) {
		(void) printf(gettext("Successfully upgraded "
		    "'%s' from version %llu to feature flags.\n"),
		    zpool_get_name(zhp), (u_longlong_t)oldversion);
	} else {
		(void) printf(gettext("Successfully upgraded "
		    "'%s' from version %llu to version %llu.\n"),
		    zpool_get_name(zhp), (u_longlong_t)oldversion,
		    (u_longlong_t)version);
	}

	return (0);
}