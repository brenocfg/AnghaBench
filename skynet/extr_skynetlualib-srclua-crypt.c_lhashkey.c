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
 int /*<<< orphan*/  Hash (char const*,int,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static int
lhashkey(lua_State *L) {
	size_t sz = 0;
	const char * key = luaL_checklstring(L, 1, &sz);
	uint8_t realkey[8];
	Hash(key,(int)sz,realkey);
	lua_pushlstring(L, (const char *)realkey, 8);
	return 1;
}