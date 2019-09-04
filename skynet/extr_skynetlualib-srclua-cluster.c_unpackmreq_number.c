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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unpack_uint32 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
unpackmreq_number(lua_State *L, const uint8_t * buf, int sz, int is_push) {
	if (sz != 13) {
		return luaL_error(L, "Invalid cluster message size %d (multi req must be 13)", sz);
	}
	uint32_t address = unpack_uint32(buf+1);
	uint32_t session = unpack_uint32(buf+5);
	uint32_t size = unpack_uint32(buf+9);
	lua_pushinteger(L, address);
	lua_pushinteger(L, session);
	lua_pushnil(L);
	lua_pushinteger(L, size);
	lua_pushboolean(L, 1);	// padding multi part
	lua_pushboolean(L, is_push);

	return 6;
}