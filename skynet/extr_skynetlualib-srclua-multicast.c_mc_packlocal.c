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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int pack (int /*<<< orphan*/ *,void*,size_t) ; 

__attribute__((used)) static int
mc_packlocal(lua_State *L) {
	void * data = lua_touserdata(L, 1);
	size_t size = (size_t)luaL_checkinteger(L, 2);
	if (size != (uint32_t)size) {
		return luaL_error(L, "Size should be 32bit integer");
	}
	return pack(L, data, size);
}