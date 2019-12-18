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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_TTABLE ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int c_lua_gettable_bypath(lua_State* L) {
	size_t len = 0;
	const char * pos = NULL;
	const char * path = lua_tolstring(L, 2, &len);
	lua_pushvalue(L, 1);
	do {
		pos = strchr(path, '.');
		if (NULL == pos) {
			lua_pushlstring(L, path, len);
		} else {
			lua_pushlstring(L, path, pos - path);
			len = len - (pos - path + 1);
			path = pos + 1;
		}
		lua_gettable(L, -2);
		if (lua_type(L, -1) != LUA_TTABLE) {
			if (NULL != pos) { // not found in path
				lua_pushnil(L);
			}
			break;
		}
		lua_remove(L, -2);
	} while(pos);
    return 1;
}