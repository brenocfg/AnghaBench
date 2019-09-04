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
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  size_t lua_Integer ;

/* Variables and functions */
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 void* unpack_uint32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
lunpackresponse(lua_State *L) {
	size_t sz;
	const char * buf = luaL_checklstring(L, 1, &sz);
	if (sz < 5) {
		return 0;
	}
	uint32_t session = unpack_uint32((const uint8_t *)buf);
	lua_pushinteger(L, (lua_Integer)session);
	switch(buf[4]) {
	case 0:	// error
		lua_pushboolean(L, 0);
		lua_pushlstring(L, buf+5, sz-5);
		return 3;
	case 1:	// ok
	case 4:	// multi end
		lua_pushboolean(L, 1);
		lua_pushlstring(L, buf+5, sz-5);
		return 3;
	case 2:	// multi begin
		if (sz != 9) {
			return 0;
		}
		sz = unpack_uint32((const uint8_t *)buf+5);
		lua_pushboolean(L, 1);
		lua_pushinteger(L, sz);
		lua_pushboolean(L, 1);
		return 4;
	case 3:	// multi part
		lua_pushboolean(L, 1);
		lua_pushlstring(L, buf+5, sz-5);
		lua_pushboolean(L, 1);
		return 4;
	default:
		return 0;
	}
}