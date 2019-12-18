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
struct skynet_context {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 char* address_port (int /*<<< orphan*/ *,char*,char const*,int,int*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 struct skynet_context* lua_touserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 scalar_t__ skynet_socket_udp_connect (struct skynet_context*,int,char const*,int) ; 

__attribute__((used)) static int
ludp_connect(lua_State *L) {
	struct skynet_context * ctx = lua_touserdata(L, lua_upvalueindex(1));
	int id = luaL_checkinteger(L, 1);
	size_t sz = 0;
	const char * addr = luaL_checklstring(L,2,&sz);
	char tmp[sz];
	int port = 0;
	const char * host = NULL;
	if (addr) {
		host = address_port(L, tmp, addr, 3, &port);
	}

	if (skynet_socket_udp_connect(ctx, id, host, port)) {
		return luaL_error(L, "udp connect failed");
	}

	return 0;
}