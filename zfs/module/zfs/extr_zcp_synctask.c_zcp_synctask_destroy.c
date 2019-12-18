#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {char const* ddsa_name; char const* ddha_name; int /*<<< orphan*/  member_0; int /*<<< orphan*/  ddsa_defer; } ;
typedef  TYPE_1__ dsl_destroy_snapshot_arg_t ;
typedef  TYPE_1__ dsl_destroy_head_arg_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  dsl_destroy_head_check ; 
 int /*<<< orphan*/  dsl_destroy_head_sync ; 
 int /*<<< orphan*/  dsl_destroy_snapshot_check ; 
 int /*<<< orphan*/  dsl_destroy_snapshot_sync ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int zcp_sync_task (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,char const*) ; 

__attribute__((used)) static int
zcp_synctask_destroy(lua_State *state, boolean_t sync, nvlist_t *err_details)
{
	int err;
	const char *dsname = lua_tostring(state, 1);

	boolean_t issnap = (strchr(dsname, '@') != NULL);

	if (!issnap && !lua_isnil(state, 2)) {
		return (luaL_error(state,
		    "'deferred' kwarg only supported for snapshots: %s",
		    dsname));
	}

	if (issnap) {
		dsl_destroy_snapshot_arg_t ddsa = { 0 };
		ddsa.ddsa_name = dsname;
		if (!lua_isnil(state, 2)) {
			ddsa.ddsa_defer = lua_toboolean(state, 2);
		} else {
			ddsa.ddsa_defer = B_FALSE;
		}

		err = zcp_sync_task(state, dsl_destroy_snapshot_check,
		    dsl_destroy_snapshot_sync, &ddsa, sync, dsname);
	} else {
		dsl_destroy_head_arg_t ddha = { 0 };
		ddha.ddha_name = dsname;

		err = zcp_sync_task(state, dsl_destroy_head_check,
		    dsl_destroy_head_sync, &ddha, sync, dsname);
	}

	return (err);
}