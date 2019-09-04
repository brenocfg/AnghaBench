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
struct skynet_socket_message {char* buffer; int type; int /*<<< orphan*/  ud; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  SKYNET_SOCKET_TYPE_ACCEPT 133 
#define  SKYNET_SOCKET_TYPE_CLOSE 132 
#define  SKYNET_SOCKET_TYPE_CONNECT 131 
#define  SKYNET_SOCKET_TYPE_DATA 130 
#define  SKYNET_SOCKET_TYPE_ERROR 129 
#define  SKYNET_SOCKET_TYPE_WARNING 128 
 int /*<<< orphan*/  TYPE_CLOSE ; 
 int /*<<< orphan*/  TYPE_ERROR ; 
 int /*<<< orphan*/  TYPE_OPEN ; 
 int /*<<< orphan*/  TYPE_WARNING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_uncomplete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int filter_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 struct skynet_socket_message* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_upvalueindex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pushstring (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
lfilter(lua_State *L) {
	struct skynet_socket_message *message = lua_touserdata(L,2);
	int size = luaL_checkinteger(L,3);
	char * buffer = message->buffer;
	if (buffer == NULL) {
		buffer = (char *)(message+1);
		size -= sizeof(*message);
	} else {
		size = -1;
	}

	lua_settop(L, 1);

	switch(message->type) {
	case SKYNET_SOCKET_TYPE_DATA:
		// ignore listen id (message->id)
		assert(size == -1);	// never padding string
		return filter_data(L, message->id, (uint8_t *)buffer, message->ud);
	case SKYNET_SOCKET_TYPE_CONNECT:
		// ignore listen fd connect
		return 1;
	case SKYNET_SOCKET_TYPE_CLOSE:
		// no more data in fd (message->id)
		close_uncomplete(L, message->id);
		lua_pushvalue(L, lua_upvalueindex(TYPE_CLOSE));
		lua_pushinteger(L, message->id);
		return 3;
	case SKYNET_SOCKET_TYPE_ACCEPT:
		lua_pushvalue(L, lua_upvalueindex(TYPE_OPEN));
		// ignore listen id (message->id);
		lua_pushinteger(L, message->ud);
		pushstring(L, buffer, size);
		return 4;
	case SKYNET_SOCKET_TYPE_ERROR:
		// no more data in fd (message->id)
		close_uncomplete(L, message->id);
		lua_pushvalue(L, lua_upvalueindex(TYPE_ERROR));
		lua_pushinteger(L, message->id);
		pushstring(L, buffer, size);
		return 4;
	case SKYNET_SOCKET_TYPE_WARNING:
		lua_pushvalue(L, lua_upvalueindex(TYPE_WARNING));
		lua_pushinteger(L, message->id);
		lua_pushinteger(L, message->ud);
		return 4;
	default:
		// never get here
		return 1;
	}
}