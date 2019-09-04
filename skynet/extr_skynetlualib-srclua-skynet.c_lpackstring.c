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
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaseri_pack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skynet_free (char*) ; 

__attribute__((used)) static int
lpackstring(lua_State *L) {
	luaseri_pack(L);
	char * str = (char *)lua_touserdata(L, -2);
	int sz = lua_tointeger(L, -1);
	lua_pushlstring(L, str, sz);
	skynet_free(str);
	return 1;
}