#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_13__ {int /*<<< orphan*/  za_first_integer; int /*<<< orphan*/  za_name; } ;
typedef  TYPE_3__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_14__ {TYPE_2__* ds_dir; } ;
typedef  TYPE_4__ dsl_dataset_t ;
struct TYPE_16__ {scalar_t__ ds_userrefs_obj; } ;
struct TYPE_15__ {int /*<<< orphan*/ * zri_pool; } ;
struct TYPE_12__ {TYPE_1__* dd_pool; } ;
struct TYPE_11__ {int /*<<< orphan*/  dp_meta_objset; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int dsl_dataset_hold_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__**) ; 
 TYPE_8__* dsl_dataset_phys (TYPE_4__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init_serialized (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  zap_cursor_serialize (int /*<<< orphan*/ *) ; 
 TYPE_5__* zcp_run_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zcp_holds_iter(lua_State *state)
{
	uint64_t dsobj = lua_tonumber(state, lua_upvalueindex(1));
	uint64_t cursor = lua_tonumber(state, lua_upvalueindex(2));
	dsl_pool_t *dp = zcp_run_info(state)->zri_pool;
	dsl_dataset_t *ds;
	zap_attribute_t za;
	zap_cursor_t zc;

	int err = dsl_dataset_hold_obj(dp, dsobj, FTAG, &ds);
	if (err == ENOENT) {
		return (0);
	} else if (err != 0) {
		return (luaL_error(state,
		    "unexpected error %d from dsl_dataset_hold_obj(dsobj)",
		    err));
	}

	if (dsl_dataset_phys(ds)->ds_userrefs_obj == 0) {
		dsl_dataset_rele(ds, FTAG);
		return (0);
	}

	zap_cursor_init_serialized(&zc, ds->ds_dir->dd_pool->dp_meta_objset,
	    dsl_dataset_phys(ds)->ds_userrefs_obj, cursor);
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

	lua_pushnumber(state, cursor);
	lua_replace(state, lua_upvalueindex(2));

	(void) lua_pushstring(state, za.za_name);
	(void) lua_pushnumber(state, za.za_first_integer);
	return (2);
}