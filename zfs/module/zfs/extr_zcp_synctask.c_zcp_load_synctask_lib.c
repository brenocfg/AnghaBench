#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zcp_synctask_info_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ zcp_synctask_destroy_info ; 
 TYPE_1__ zcp_synctask_promote_info ; 
 TYPE_1__ zcp_synctask_rollback_info ; 
 TYPE_1__ zcp_synctask_snapshot_info ; 
 int /*<<< orphan*/  zcp_synctask_wrapper ; 

int
zcp_load_synctask_lib(lua_State *state, boolean_t sync)
{
	int i;
	zcp_synctask_info_t *zcp_synctask_funcs[] = {
		&zcp_synctask_destroy_info,
		&zcp_synctask_promote_info,
		&zcp_synctask_rollback_info,
		&zcp_synctask_snapshot_info,
		NULL
	};

	lua_newtable(state);

	for (i = 0; zcp_synctask_funcs[i] != NULL; i++) {
		zcp_synctask_info_t *info = zcp_synctask_funcs[i];
		lua_pushlightuserdata(state, info);
		lua_pushboolean(state, sync);
		lua_pushcclosure(state, &zcp_synctask_wrapper, 2);
		lua_setfield(state, -2, info->name);
		info++;
	}

	return (1);
}