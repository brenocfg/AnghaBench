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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_buffer (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  unpack_uint32 (int const*) ; 

__attribute__((used)) static int
unpackmreq_part(lua_State *L, const uint8_t * buf, int sz) {
	if (sz < 5) {
		return luaL_error(L, "Invalid cluster multi part message");
	}
	int padding = (buf[0] == 2);
	uint32_t session = unpack_uint32(buf+1);
	lua_pushboolean(L, 0);	// no address
	lua_pushinteger(L, session);
	return_buffer(L, (const char *)buf+5, sz-5);
	lua_pushboolean(L, padding);

	return 5;
}