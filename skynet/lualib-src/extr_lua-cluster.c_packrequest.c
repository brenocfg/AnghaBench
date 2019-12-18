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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int INT32_MAX ; 
 int LUA_TNUMBER ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  packreq_multi (int /*<<< orphan*/ *,int,void*,int) ; 
 int packreq_number (int /*<<< orphan*/ *,int,void*,int,int) ; 
 int packreq_string (int /*<<< orphan*/ *,int,void*,int,int) ; 
 int /*<<< orphan*/  skynet_free (void*) ; 

__attribute__((used)) static int
packrequest(lua_State *L, int is_push) {
	void *msg = lua_touserdata(L,3);
	if (msg == NULL) {
		return luaL_error(L, "Invalid request message");
	}
	uint32_t sz = (uint32_t)luaL_checkinteger(L,4);
	int session = luaL_checkinteger(L,2);
	if (session <= 0) {
		skynet_free(msg);
		return luaL_error(L, "Invalid request session %d", session);
	}
	int addr_type = lua_type(L,1);
	int multipak;
	if (addr_type == LUA_TNUMBER) {
		multipak = packreq_number(L, session, msg, sz, is_push);
	} else {
		multipak = packreq_string(L, session, msg, sz, is_push);
	}
	uint32_t new_session = (uint32_t)session + 1;
	if (new_session > INT32_MAX) {
		new_session = 1;
	}
	lua_pushinteger(L, new_session);
	if (multipak) {
		lua_createtable(L, multipak, 0);
		packreq_multi(L, session, msg, sz);
		skynet_free(msg);
		return 3;
	} else {
		skynet_free(msg);
		return 2;
	}
}