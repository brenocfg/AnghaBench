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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  LUA_TBOOLEAN 132 
#define  LUA_TNIL 131 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int lsubtype (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int) ; 
 int lua_upvalueindex (int) ; 

__attribute__((used)) static int
ltype(lua_State *L) {
	int t = lua_type(L,1);
	int type = 0;
	switch (t) {
	case LUA_TNUMBER:
		type = 1;
		break;
	case LUA_TBOOLEAN:
		type = 2;
		break;
	case LUA_TTABLE:
		type = 3;
		break;
	case LUA_TNIL:
		lua_pushvalue(L, lua_upvalueindex(4));
		return 1;
	case LUA_TSTRING: {
		size_t len = 0;
		const char * str = lua_tolstring(L,1,&len);
		if (str[0] == 0 && len >= 2) {
			return lsubtype(L, (uint8_t)str[1], (const uint8_t *)str+2, len-2);
		} else {
			type = 5;
			break;
		}
	}
	default:
		return luaL_error(L, "Invalid type %s",lua_typename(L,t));
	}
	lua_pushvalue(L, lua_upvalueindex(type));
	lua_pushvalue(L,1);
	return 2;
}