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
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,int) ; 
 void* skynet_malloc (int) ; 

__attribute__((used)) static void
return_buffer(lua_State *L, const char * buffer, int sz) {
	void * ptr = skynet_malloc(sz);
	memcpy(ptr, buffer, sz);
	lua_pushlightuserdata(L, ptr);
	lua_pushinteger(L, sz);
}