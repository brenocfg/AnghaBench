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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int EINVAL ; 
#define  LUA_TBOOLEAN 132 
#define  LUA_TNIL 131 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_boolean_value (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_int64 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int lua_absindex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_checkstack (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * zcp_table_to_nvlist (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
zcp_lua_to_nvlist_impl(lua_State *state, int index, nvlist_t *nvl,
    const char *key, int depth)
{
	/*
	 * Verify that we have enough remaining space in the lua stack to parse
	 * a key-value pair and push an error.
	 */
	if (!lua_checkstack(state, 3)) {
		(void) lua_pushstring(state, "Lua stack overflow");
		return (1);
	}

	index = lua_absindex(state, index);

	switch (lua_type(state, index)) {
	case LUA_TNIL:
		fnvlist_add_boolean(nvl, key);
		break;
	case LUA_TBOOLEAN:
		fnvlist_add_boolean_value(nvl, key,
		    lua_toboolean(state, index));
		break;
	case LUA_TNUMBER:
		fnvlist_add_int64(nvl, key, lua_tonumber(state, index));
		break;
	case LUA_TSTRING:
		fnvlist_add_string(nvl, key, lua_tostring(state, index));
		break;
	case LUA_TTABLE: {
		nvlist_t *value_nvl = zcp_table_to_nvlist(state, index, depth);
		if (value_nvl == NULL)
			return (EINVAL);

		fnvlist_add_nvlist(nvl, key, value_nvl);
		fnvlist_free(value_nvl);
		break;
	}
	default:
		(void) lua_pushfstring(state,
		    "Invalid value type '%s' for key '%s'",
		    lua_typename(state, lua_type(state, index)), key);
		return (EINVAL);
	}

	return (0);
}