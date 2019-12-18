#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* p_tcp ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int IO_DONE ; 
 int /*<<< orphan*/  auxiliar_checkclass (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  auxiliar_setclass (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ luaL_optnumber (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int socket_listen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  socket_strerror (int) ; 

__attribute__((used)) static int meth_listen(lua_State *L)
{
    p_tcp tcp = (p_tcp) auxiliar_checkclass(L, "tcp{master}", 1);
    int backlog = (int) luaL_optnumber(L, 2, 32);
    int err = socket_listen(&tcp->sock, backlog);
    if (err != IO_DONE) {
        lua_pushnil(L);
        lua_pushstring(L, socket_strerror(err));
        return 2;
    }
    /* turn master object into a server object */
    auxiliar_setclass(L, "tcp{server}", 1);
    lua_pushnumber(L, 1);
    return 1;
}