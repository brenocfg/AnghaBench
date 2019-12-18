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
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/ * skynet_malloc (size_t) ; 
 char* tolstring (int /*<<< orphan*/ *,size_t*,int) ; 
 int /*<<< orphan*/  write_size (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
lpack(lua_State *L) {
	size_t len;
	const char * ptr = tolstring(L, &len, 1);
	if (len >= 0x10000) {
		return luaL_error(L, "Invalid size (too long) of data : %d", (int)len);
	}

	uint8_t * buffer = skynet_malloc(len + 2);
	write_size(buffer, len);
	memcpy(buffer+2, ptr, len);

	lua_pushlightuserdata(L, buffer);
	lua_pushinteger(L, len + 2);

	return 2;
}