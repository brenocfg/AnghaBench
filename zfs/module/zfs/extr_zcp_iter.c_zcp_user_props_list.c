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
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_4__ {int /*<<< orphan*/ * zri_pool; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_from_ds (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_prop_get_all (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * zcp_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* zcp_run_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcp_user_props_iter ; 
 TYPE_1__ zcp_user_props_list_info ; 

__attribute__((used)) static int
zcp_user_props_list(lua_State *state)
{
	const char *dsname = lua_tostring(state, 1);
	dsl_pool_t *dp = zcp_run_info(state)->zri_pool;
	objset_t *os;
	nvlist_t **props = lua_newuserdata(state, sizeof (nvlist_t *));

	dsl_dataset_t *ds = zcp_dataset_hold(state, dp, dsname, FTAG);
	if (ds == NULL)
		return (1); /* not reached; zcp_dataset_hold() longjmp'd */
	VERIFY0(dmu_objset_from_ds(ds, &os));
	VERIFY0(dsl_prop_get_all(os, props));
	dsl_dataset_rele(ds, FTAG);

	/*
	 * Set the metatable for the properties list to free it on
	 * completion.
	 */
	luaL_getmetatable(state, zcp_user_props_list_info.name);
	(void) lua_setmetatable(state, -2);

	lua_pushlightuserdata(state, NULL);
	lua_pushcclosure(state, &zcp_user_props_iter, 2);
	return (1);
}