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
 void* get_buffer (int /*<<< orphan*/ *,int,int*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 struct skynet_context* lua_touserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 int skynet_socket_send (struct skynet_context*,int,void*,int) ; 

__attribute__((used)) static int
lsend(lua_State *L) {
	struct skynet_context * ctx = lua_touserdata(L, lua_upvalueindex(1));
	int id = luaL_checkinteger(L, 1);
	int sz = 0;
	void *buffer = get_buffer(L, 2, &sz);
	int err = skynet_socket_send(ctx, id, buffer, sz);
	lua_pushboolean(L, !err);
	return 1;
}