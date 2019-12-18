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
 int /*<<< orphan*/  auxiliar_checkclass (int /*<<< orphan*/ *,char*,int) ; 
 int luaL_checkoption (int /*<<< orphan*/ *,int,char*,char const**) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  socket_shutdown (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int meth_shutdown(lua_State *L)
{
    /* SHUT_RD,  SHUT_WR,  SHUT_RDWR  have  the value 0, 1, 2, so we can use method index directly */
    static const char* methods[] = { "receive", "send", "both", NULL };
    p_tcp tcp = (p_tcp) auxiliar_checkclass(L, "tcp{client}", 1);
    int how = luaL_checkoption(L, 2, "both", methods);
    socket_shutdown(&tcp->sock, how);
    lua_pushnumber(L, 1);
    return 1;
}