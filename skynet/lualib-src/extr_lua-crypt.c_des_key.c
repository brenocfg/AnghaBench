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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  des_main_ks (int /*<<< orphan*/ *,void const*) ; 
 void* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
des_key(lua_State *L, uint32_t SK[32]) {
	size_t keysz = 0;
	const void * key = luaL_checklstring(L, 1, &keysz);
	if (keysz != 8) {
		luaL_error(L, "Invalid key size %d, need 8 bytes", (int)keysz);
	}
	des_main_ks(SK, key);
}