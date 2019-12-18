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
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int /*<<< orphan*/  sock; int /*<<< orphan*/  tm; } ;

/* Variables and functions */
 int IO_CLOSED ; 
 int IO_DONE ; 
 size_t MIN (size_t,int) ; 
 int UDP_DATAGRAMSIZE ; 
 int /*<<< orphan*/  auxiliar_checkgroup (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  luaL_optnumber (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int socket_recv (int /*<<< orphan*/ *,char*,size_t,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_markstart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_strerror (int) ; 

__attribute__((used)) static int meth_receive(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    char buffer[UDP_DATAGRAMSIZE];
    size_t got, count = (size_t) luaL_optnumber(L, 2, sizeof(buffer));
    int err;
    p_timeout tm = &udp->tm;
    count = MIN(count, sizeof(buffer));
    timeout_markstart(tm);
    err = socket_recv(&udp->sock, buffer, count, &got, tm);
    /* Unlike TCP, recv() of zero is not closed, but a zero-length packet. */
    if (err == IO_CLOSED)
        err = IO_DONE;
    if (err != IO_DONE) {
        lua_pushnil(L);
        lua_pushstring(L, udp_strerror(err));
        return 2;
    }
    lua_pushlstring(L, buffer, got);
    return 1;
}