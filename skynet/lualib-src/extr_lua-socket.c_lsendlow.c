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
struct socket_sendbuffer {int id; } ;
struct skynet_context {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  get_buffer (int /*<<< orphan*/ *,int,struct socket_sendbuffer*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 struct skynet_context* lua_touserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_upvalueindex (int) ; 
 int skynet_socket_sendbuffer_lowpriority (struct skynet_context*,struct socket_sendbuffer*) ; 

__attribute__((used)) static int
lsendlow(lua_State *L) {
	struct skynet_context * ctx = lua_touserdata(L, lua_upvalueindex(1));
	int id = luaL_checkinteger(L, 1);
	struct socket_sendbuffer buf;
	buf.id = id;
	get_buffer(L, 2, &buf);
	int err = skynet_socket_sendbuffer_lowpriority(ctx, &buf);
	lua_pushboolean(L, !err);
	return 1;
}