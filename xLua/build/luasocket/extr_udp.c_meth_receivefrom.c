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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  TYPE_1__* p_udp ;
typedef  int /*<<< orphan*/ * p_timeout ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_2__ {int /*<<< orphan*/  sock; int /*<<< orphan*/  tm; } ;
typedef  int /*<<< orphan*/  SA ;

/* Variables and functions */
 int INET6_ADDRSTRLEN ; 
 int IO_CLOSED ; 
 int IO_DONE ; 
 size_t MIN (size_t,int) ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int UDP_DATAGRAMSIZE ; 
 int /*<<< orphan*/  auxiliar_checkclass (int /*<<< orphan*/ *,char*,int) ; 
 char* gai_strerror (int) ; 
 int getnameinfo (struct sockaddr*,int,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  luaL_optnumber (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int socket_recvfrom (int /*<<< orphan*/ *,char*,size_t,size_t*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ strtol (char*,char**,int) ; 
 int /*<<< orphan*/  timeout_markstart (int /*<<< orphan*/ *) ; 
 char* udp_strerror (int) ; 

__attribute__((used)) static int meth_receivefrom(lua_State *L)
{
    p_udp udp = (p_udp) auxiliar_checkclass(L, "udp{unconnected}", 1);
    char buffer[UDP_DATAGRAMSIZE];
    size_t got, count = (size_t) luaL_optnumber(L, 2, sizeof(buffer));
    int err;
    p_timeout tm = &udp->tm;
    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof(addr);
    char addrstr[INET6_ADDRSTRLEN];
    char portstr[6];
    timeout_markstart(tm);
    count = MIN(count, sizeof(buffer));
    err = socket_recvfrom(&udp->sock, buffer, count, &got, (SA *) &addr, 
            &addr_len, tm);
    /* Unlike TCP, recv() of zero is not closed, but a zero-length packet. */
    if (err == IO_CLOSED)
        err = IO_DONE;
    if (err != IO_DONE) {
        lua_pushnil(L);
        lua_pushstring(L, udp_strerror(err));
        return 2;
    }
    err = getnameinfo((struct sockaddr *)&addr, addr_len, addrstr, 
        INET6_ADDRSTRLEN, portstr, 6, NI_NUMERICHOST | NI_NUMERICSERV);
	if (err) {
        lua_pushnil(L);
        lua_pushstring(L, gai_strerror(err));
        return 2;
    }
    lua_pushlstring(L, buffer, got);
    lua_pushstring(L, addrstr);
    lua_pushinteger(L, (int) strtol(portstr, (char **) NULL, 10));
    return 3;
}