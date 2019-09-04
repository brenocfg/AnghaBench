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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_buffer (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ unpack_uint32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
unpackreq_number(lua_State *L, const uint8_t * buf, int sz) {
	if (sz < 9) {
		return luaL_error(L, "Invalid cluster message (size=%d)", sz);
	}
	uint32_t address = unpack_uint32(buf+1);
	uint32_t session = unpack_uint32(buf+5);
	lua_pushinteger(L, address);
	lua_pushinteger(L, session);

	return_buffer(L, (const char *)buf+9, sz-9);
	if (session == 0) {
		lua_pushnil(L);
		lua_pushboolean(L,1);	// is_push, no reponse
		return 6;
	}

	return 4;
}