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
typedef  scalar_t__ uint32_t ;
struct skynet_context {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  LUA_TLIGHTUSERDATA 129 
 int LUA_TNUMBER ; 
#define  LUA_TSTRING 128 
 int PTYPE_TAG_ALLOCSESSION ; 
 int PTYPE_TAG_DONTCOPY ; 
 char* get_dest_string (int /*<<< orphan*/ *,int) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 void* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int) ; 
 int lua_upvalueindex (int) ; 
 int skynet_send (struct skynet_context*,int,scalar_t__,int,int,void*,int) ; 
 int skynet_sendname (struct skynet_context*,int,char const*,int,int,void*,int) ; 

__attribute__((used)) static int
send_message(lua_State *L, int source, int idx_type) {
	struct skynet_context * context = lua_touserdata(L, lua_upvalueindex(1));
	uint32_t dest = (uint32_t)lua_tointeger(L, 1);
	const char * dest_string = NULL;
	if (dest == 0) {
		if (lua_type(L,1) == LUA_TNUMBER) {
			return luaL_error(L, "Invalid service address 0");
		}
		dest_string = get_dest_string(L, 1);
	}

	int type = luaL_checkinteger(L, idx_type+0);
	int session = 0;
	if (lua_isnil(L,idx_type+1)) {
		type |= PTYPE_TAG_ALLOCSESSION;
	} else {
		session = luaL_checkinteger(L,idx_type+1);
	}

	int mtype = lua_type(L,idx_type+2);
	switch (mtype) {
	case LUA_TSTRING: {
		size_t len = 0;
		void * msg = (void *)lua_tolstring(L,idx_type+2,&len);
		if (len == 0) {
			msg = NULL;
		}
		if (dest_string) {
			session = skynet_sendname(context, source, dest_string, type, session , msg, len);
		} else {
			session = skynet_send(context, source, dest, type, session , msg, len);
		}
		break;
	}
	case LUA_TLIGHTUSERDATA: {
		void * msg = lua_touserdata(L,idx_type+2);
		int size = luaL_checkinteger(L,idx_type+3);
		if (dest_string) {
			session = skynet_sendname(context, source, dest_string, type | PTYPE_TAG_DONTCOPY, session, msg, size);
		} else {
			session = skynet_send(context, source, dest, type | PTYPE_TAG_DONTCOPY, session, msg, size);
		}
		break;
	}
	default:
		luaL_error(L, "invalid param %s", lua_typename(L, lua_type(L,idx_type+2)));
	}
	if (session < 0) {
		if (session == -2) {
			// package is too large
			lua_pushboolean(L, 0);
			return 1;
		}
		// send to invalid address
		// todo: maybe throw an error would be better
		return 0;
	}
	lua_pushinteger(L,session);
	return 1;
}