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
typedef  TYPE_1__* p_udp ;
typedef  int /*<<< orphan*/ * p_timeout ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;
struct TYPE_2__ {int /*<<< orphan*/  sock; int /*<<< orphan*/  tm; } ;

/* Variables and functions */
 int IO_DONE ; 
 int /*<<< orphan*/  auxiliar_checkclass (int /*<<< orphan*/ *,char*,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int socket_send (int /*<<< orphan*/ *,char const*,size_t,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_markstart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_strerror (int) ; 

__attribute__((used)) static int meth_send(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkclass(L, "udp{connected}", 1);
    p_timeout tm = &udp->tm;
    size_t count, sent = 0;
    int err;
    const char *data = luaL_checklstring(L, 2, &count);
    timeout_markstart(tm);
    err = socket_send(&udp->sock, data, count, &sent, tm);
    if (err != IO_DONE) {
        lua_pushnil(L);
        lua_pushstring(L, udp_strerror(err));
        return 2;
    }
    lua_pushnumber(L, (lua_Number) sent);
    return 1;
}