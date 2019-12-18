#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_11__ {int /*<<< orphan*/  za_first_integer; } ;
typedef  TYPE_1__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_12__ {int /*<<< orphan*/  dp_meta_objset; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_13__ {int /*<<< orphan*/  ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_15__ {scalar_t__ ds_next_clones_obj; } ;
struct TYPE_14__ {TYPE_2__* zri_pool; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int dsl_dataset_hold_obj (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 TYPE_7__* dsl_dataset_phys (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_name (int /*<<< orphan*/ ,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init_serialized (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zap_cursor_serialize (int /*<<< orphan*/ *) ; 
 TYPE_4__* zcp_run_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zcp_clones_iter(lua_State *state)
{
	int err;
	char clonename[ZFS_MAX_DATASET_NAME_LEN];
	uint64_t dsobj = lua_tonumber(state, lua_upvalueindex(1));
	uint64_t cursor = lua_tonumber(state, lua_upvalueindex(2));
	dsl_pool_t *dp = zcp_run_info(state)->zri_pool;
	dsl_dataset_t *ds, *clone;
	zap_attribute_t za;
	zap_cursor_t zc;

	err = dsl_dataset_hold_obj(dp, dsobj, FTAG, &ds);
	if (err == ENOENT) {
		return (0);
	} else if (err != 0) {
		return (luaL_error(state,
		    "unexpected error %d from dsl_dataset_hold_obj(dsobj)",
		    err));
	}

	if (dsl_dataset_phys(ds)->ds_next_clones_obj == 0) {
		dsl_dataset_rele(ds, FTAG);
		return (0);
	}

	zap_cursor_init_serialized(&zc, dp->dp_meta_objset,
	    dsl_dataset_phys(ds)->ds_next_clones_obj, cursor);
	dsl_dataset_rele(ds, FTAG);

	err = zap_cursor_retrieve(&zc, &za);
	if (err != 0) {
		zap_cursor_fini(&zc);
		if (err != ENOENT) {
			return (luaL_error(state,
			    "unexpected error %d from zap_cursor_retrieve()",
			    err));
		}
		return (0);
	}
	zap_cursor_advance(&zc);
	cursor = zap_cursor_serialize(&zc);
	zap_cursor_fini(&zc);

	err = dsl_dataset_hold_obj(dp, za.za_first_integer, FTAG, &clone);
	if (err != 0) {
		return (luaL_error(state,
		    "unexpected error %d from "
		    "dsl_dataset_hold_obj(za_first_integer)", err));
	}

	dsl_dir_name(clone->ds_dir, clonename);
	dsl_dataset_rele(clone, FTAG);

	lua_pushnumber(state, cursor);
	lua_replace(state, lua_upvalueindex(2));

	(void) lua_pushstring(state, clonename);
	return (1);
}