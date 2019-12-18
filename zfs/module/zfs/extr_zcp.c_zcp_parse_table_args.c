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
 int LUA_TNIL ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  zcp_args_error (int /*<<< orphan*/ *,char const*,TYPE_1__ const*,TYPE_1__ const*,char*,...) ; 

__attribute__((used)) static void
zcp_parse_table_args(lua_State *state, const char *fname,
    const zcp_arg_t *pargs, const zcp_arg_t *kwargs)
{
	int i;
	int type;

	for (i = 0; pargs[i].za_name != NULL; i++) {
		/*
		 * Check the table for this positional argument, leaving it
		 * on the top of the stack once we finish validating it.
		 */
		lua_pushinteger(state, i + 1);
		lua_gettable(state, 1);

		type = lua_type(state, -1);
		if (type == LUA_TNIL) {
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

		/*
		 * Remove the positional argument from the table.
		 */
		lua_pushinteger(state, i + 1);
		lua_pushnil(state);
		lua_settable(state, 1);
	}

	for (i = 0; kwargs[i].za_name != NULL; i++) {
		/*
		 * Check the table for this keyword argument, which may be
		 * nil if it was omitted. Leave the value on the top of
		 * the stack after validating it.
		 */
		lua_getfield(state, 1, kwargs[i].za_name);

		type = lua_type(state, -1);
		if (type != LUA_TNIL && type != kwargs[i].za_lua_type) {
			zcp_args_error(state, fname, pargs, kwargs,
			    "kwarg '%s' wrong type (is '%s', expected '%s')",
			    kwargs[i].za_name, lua_typename(state, type),
			    lua_typename(state, kwargs[i].za_lua_type));
			panic("unreachable code");
		}

		/*
		 * Remove the keyword argument from the table.
		 */
		lua_pushnil(state);
		lua_setfield(state, 1, kwargs[i].za_name);
	}

	/*
	 * Any entries remaining in the table are invalid inputs, print
	 * an error message based on what the entry is.
	 */
	lua_pushnil(state);
	if (lua_next(state, 1)) {
		if (lua_isnumber(state, -2) && lua_tointeger(state, -2) > 0) {
			zcp_args_error(state, fname, pargs, kwargs,
			    "too many positional arguments");
		} else if (lua_isstring(state, -2)) {
			zcp_args_error(state, fname, pargs, kwargs,
			    "invalid kwarg '%s'", lua_tostring(state, -2));
		} else {
			zcp_args_error(state, fname, pargs, kwargs,
			    "kwarg keys must be strings");
		}
		panic("unreachable code");
	}

	lua_remove(state, 1);
}