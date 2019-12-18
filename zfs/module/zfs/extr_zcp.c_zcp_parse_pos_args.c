#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int za_lua_type; int /*<<< orphan*/ * za_name; } ;
typedef  TYPE_1__ zcp_arg_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int LUA_TNONE ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  zcp_args_error (int /*<<< orphan*/ *,char const*,TYPE_1__ const*,TYPE_1__ const*,char*,...) ; 

__attribute__((used)) static void
zcp_parse_pos_args(lua_State *state, const char *fname, const zcp_arg_t *pargs,
    const zcp_arg_t *kwargs)
{
	int i;
	int type;

	for (i = 0; pargs[i].za_name != NULL; i++) {
		type = lua_type(state, i + 1);
		if (type == LUA_TNONE) {
			zcp_args_error(state, fname, pargs, kwargs,
			    "too few arguments");
			panic("unreachable code");
		} else if (type != pargs[i].za_lua_type) {
			zcp_args_error(state, fname, pargs, kwargs,
			    "arg %d wrong type (is '%s', expected '%s')",
			    i + 1, lua_typename(state, type),
			    lua_typename(state, pargs[i].za_lua_type));
			panic("unreachable code");
		}
	}
	if (lua_gettop(state) != i) {
		zcp_args_error(state, fname, pargs, kwargs,
		    "too many positional arguments");
		panic("unreachable code");
	}

	for (i = 0; kwargs[i].za_name != NULL; i++) {
		lua_pushnil(state);
	}
}