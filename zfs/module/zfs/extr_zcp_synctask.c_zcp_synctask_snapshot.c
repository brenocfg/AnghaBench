#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zri_cred; TYPE_1__* zri_pool; } ;
typedef  TYPE_2__ zcp_run_info_t ;
typedef  int /*<<< orphan*/  zcp_cleanup_t ;
typedef  int /*<<< orphan*/  zcp_cleanup_handler_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_8__ {int /*<<< orphan*/  ddsa_snaps; int /*<<< orphan*/  ddsa_cr; int /*<<< orphan*/ * ddsa_props; int /*<<< orphan*/ * ddsa_errors; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ dsl_dataset_snapshot_arg_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  dp_spa; } ;

/* Variables and functions */
 int ENOTSUP ; 
 scalar_t__ SPA_VERSION_FAST_SNAP ; 
 int /*<<< orphan*/  dsl_dataset_snapshot_check ; 
 int /*<<< orphan*/  dsl_dataset_snapshot_sync ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ ) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcp_deregister_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zcp_register_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* zcp_run_info (int /*<<< orphan*/ *) ; 
 int zcp_sync_task (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
zcp_synctask_snapshot(lua_State *state, boolean_t sync, nvlist_t *err_details)
{
	int err;
	dsl_dataset_snapshot_arg_t ddsa = { 0 };
	const char *dsname = lua_tostring(state, 1);
	zcp_run_info_t *ri = zcp_run_info(state);

	/*
	 * On old pools, the ZIL must not be active when a snapshot is created,
	 * but we can't suspend the ZIL because we're already in syncing
	 * context.
	 */
	if (spa_version(ri->zri_pool->dp_spa) < SPA_VERSION_FAST_SNAP) {
		return (ENOTSUP);
	}

	/*
	 * We only allow for a single snapshot rather than a list, so the
	 * error list output is unnecessary.
	 */
	ddsa.ddsa_errors = NULL;
	ddsa.ddsa_props = NULL;
	ddsa.ddsa_cr = ri->zri_cred;
	ddsa.ddsa_snaps = fnvlist_alloc();
	fnvlist_add_boolean(ddsa.ddsa_snaps, dsname);

	zcp_cleanup_handler_t *zch = zcp_register_cleanup(state,
	    (zcp_cleanup_t *)&fnvlist_free, ddsa.ddsa_snaps);

	err = zcp_sync_task(state, dsl_dataset_snapshot_check,
	    dsl_dataset_snapshot_sync, &ddsa, sync, dsname);

	zcp_deregister_cleanup(state, zch);
	fnvlist_free(ddsa.ddsa_snaps);

	return (err);
}