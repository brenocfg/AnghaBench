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
struct addrinfo {int ai_flags; scalar_t__ ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  TYPE_1__* p_udp ;
typedef  int /*<<< orphan*/ * p_timeout ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  aihint ;
struct TYPE_2__ {int /*<<< orphan*/  sock; int /*<<< orphan*/  family; int /*<<< orphan*/  tm; } ;

/* Variables and functions */
 int AI_NUMERICHOST ; 
 int AI_NUMERICSERV ; 
 int IO_DONE ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  auxiliar_checkclass (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int socket_sendto (int /*<<< orphan*/ *,char const*,size_t,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_markstart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_strerror (int) ; 

__attribute__((used)) static int meth_sendto(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkclass(L, "udp{unconnected}", 1);
    size_t count, sent = 0;
    const char *data = luaL_checklstring(L, 2, &count);
    const char *ip = luaL_checkstring(L, 3);
    const char *port = luaL_checkstring(L, 4);
    p_timeout tm = &udp->tm;
    int err;
    struct addrinfo aihint;
    struct addrinfo *ai;
    memset(&aihint, 0, sizeof(aihint));
    aihint.ai_family = udp->family;
    aihint.ai_socktype = SOCK_DGRAM;
    aihint.ai_flags = AI_NUMERICHOST | AI_NUMERICSERV;
    err = getaddrinfo(ip, port, &aihint, &ai);
	if (err) {
        lua_pushnil(L);
        lua_pushstring(L, gai_strerror(err));
        return 2;
    }
    timeout_markstart(tm);
    err = socket_sendto(&udp->sock, data, count, &sent, ai->ai_addr, 
        (socklen_t) ai->ai_addrlen, tm);
    freeaddrinfo(ai);
    if (err != IO_DONE) {
        lua_pushnil(L);
        lua_pushstring(L, udp_strerror(err));
        return 2;
    }
    lua_pushnumber(L, (lua_Number) sent);
    return 1;
}