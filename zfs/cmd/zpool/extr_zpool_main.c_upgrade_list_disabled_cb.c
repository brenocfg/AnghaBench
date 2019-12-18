#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zpool_handle_t ;
struct TYPE_3__ {void* cb_first; } ;
typedef  TYPE_1__ upgrade_cbdata_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  void* boolean_t ;
struct TYPE_4__ {char* fi_guid; char* fi_uname; } ;

/* Variables and functions */
 void* B_FALSE ; 
 void* B_TRUE ; 
 int SPA_FEATURES ; 
 scalar_t__ SPA_VERSION_FEATURES ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VERSION ; 
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  history_str ; 
 void* log_history ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_2__* spa_feature_table ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_features (int /*<<< orphan*/ *) ; 
 char* zpool_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_log_history (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
upgrade_list_disabled_cb(zpool_handle_t *zhp, void *arg)
{
	upgrade_cbdata_t *cbp = arg;
	nvlist_t *config;
	uint64_t version;

	config = zpool_get_config(zhp, NULL);
	verify(nvlist_lookup_uint64(config, ZPOOL_CONFIG_VERSION,
	    &version) == 0);

	if (version >= SPA_VERSION_FEATURES) {
		int i;
		boolean_t poolfirst = B_TRUE;
		nvlist_t *enabled = zpool_get_features(zhp);

		for (i = 0; i < SPA_FEATURES; i++) {
			const char *fguid = spa_feature_table[i].fi_guid;
			const char *fname = spa_feature_table[i].fi_uname;
			if (!nvlist_exists(enabled, fguid)) {
				if (cbp->cb_first) {
					(void) printf(gettext("\nSome "
					    "supported features are not "
					    "enabled on the following pools. "
					    "Once a\nfeature is enabled the "
					    "pool may become incompatible with "
					    "software\nthat does not support "
					    "the feature. See "
					    "zpool-features(5) for "
					    "details.\n\n"));
					(void) printf(gettext("POOL  "
					    "FEATURE\n"));
					(void) printf(gettext("------"
					    "---------\n"));
					cbp->cb_first = B_FALSE;
				}

				if (poolfirst) {
					(void) printf(gettext("%s\n"),
					    zpool_get_name(zhp));
					poolfirst = B_FALSE;
				}

				(void) printf(gettext("      %s\n"), fname);
			}
			/*
			 * If they did "zpool upgrade -a", then we could
			 * be doing ioctls to different pools.  We need
			 * to log this history once to each pool, and bypass
			 * the normal history logging that happens in main().
			 */
			(void) zpool_log_history(g_zfs, history_str);
			log_history = B_FALSE;
		}
	}

	return (0);
}