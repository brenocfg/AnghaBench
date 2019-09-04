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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  luaL_Buffer ;
typedef  int /*<<< orphan*/  inc ;
typedef  int /*<<< orphan*/  i ;
typedef  int /*<<< orphan*/  d ;

/* Variables and functions */
 int /*<<< orphan*/  BSON_TIMESTAMP ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ltimestamp(lua_State *L) {
	int d = luaL_checkinteger(L,1);
	luaL_Buffer b;
	luaL_buffinit(L, &b);
	luaL_addchar(&b, 0);
	luaL_addchar(&b, BSON_TIMESTAMP);
	if (lua_isnoneornil(L,2)) {
		static uint32_t inc = 0;
		luaL_addlstring(&b, (const char *)&inc, sizeof(inc));
		++inc;
	} else {
		uint32_t i = (uint32_t)lua_tointeger(L,2);
		luaL_addlstring(&b, (const char *)&i, sizeof(i));
	}
	luaL_addlstring(&b, (const char *)&d, sizeof(d));
	luaL_pushresult(&b);

	return 1;
}