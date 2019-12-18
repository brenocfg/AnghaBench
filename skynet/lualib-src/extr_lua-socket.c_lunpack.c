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
struct skynet_socket_message {scalar_t__ type; scalar_t__ id; scalar_t__ ud; int /*<<< orphan*/ * buffer; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ SKYNET_SOCKET_TYPE_UDP ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 struct skynet_socket_message* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 char* skynet_socket_udp_address (struct skynet_socket_message*,int*) ; 

__attribute__((used)) static int
lunpack(lua_State *L) {
	struct skynet_socket_message *message = lua_touserdata(L,1);
	int size = luaL_checkinteger(L,2);

	lua_pushinteger(L, message->type);
	lua_pushinteger(L, message->id);
	lua_pushinteger(L, message->ud);
	if (message->buffer == NULL) {
		lua_pushlstring(L, (char *)(message+1),size - sizeof(*message));
	} else {
		lua_pushlightuserdata(L, message->buffer);
	}
	if (message->type == SKYNET_SOCKET_TYPE_UDP) {
		int addrsz = 0;
		const char * addrstring = skynet_socket_udp_address(message, &addrsz);
		if (addrstring) {
			lua_pushlstring(L, addrstring, addrsz);
			return 5;
		}
	}
	return 4;
}