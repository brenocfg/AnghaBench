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
 int LUA_TLIGHTUSERDATA ; 
 int LUA_TSTRING ; 
 int LUA_TUSERDATA ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 size_t luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 void* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const void *
getbuffer(lua_State *L, int index, size_t *sz) {
	const void * buffer = NULL;
	int t = lua_type(L, index);
	if (t == LUA_TSTRING) {
		buffer = lua_tolstring(L, index, sz);
	} else {
		if (t != LUA_TUSERDATA && t != LUA_TLIGHTUSERDATA) {
			luaL_argerror(L, index, "Need a string or userdata");
			return NULL;
		}
		buffer = lua_touserdata(L, index);
		*sz = luaL_checkinteger(L, index+1);
	}
	return buffer;
}