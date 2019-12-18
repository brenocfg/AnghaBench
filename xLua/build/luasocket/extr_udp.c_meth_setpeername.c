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
struct addrinfo {int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_socktype; } ;
typedef  TYPE_1__* p_udp ;
typedef  int /*<<< orphan*/ * p_timeout ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  connecthints ;
struct TYPE_2__ {int /*<<< orphan*/  family; int /*<<< orphan*/  sock; int /*<<< orphan*/  tm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  auxiliar_checkgroup (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  auxiliar_setclass (int /*<<< orphan*/ *,char*,int) ; 
 char* inet_tryconnect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,struct addrinfo*) ; 
 int /*<<< orphan*/  inet_trydisconnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int strcmp (char const*,char*) ; 

__attribute__((used)) static int meth_setpeername(lua_State *L) {
    p_udp udp = (p_udp) auxiliar_checkgroup(L, "udp{any}", 1);
    p_timeout tm = &udp->tm;
    const char *address = luaL_checkstring(L, 2);
    int connecting = strcmp(address, "*");
    const char *port = connecting? luaL_checkstring(L, 3): "0";
    struct addrinfo connecthints;
    const char *err;
    memset(&connecthints, 0, sizeof(connecthints));
    connecthints.ai_socktype = SOCK_DGRAM;
    /* make sure we try to connect only to the same family */
    connecthints.ai_family = udp->family;
    if (connecting) {
        err = inet_tryconnect(&udp->sock, &udp->family, address, 
            port, tm, &connecthints);
        if (err) {
            lua_pushnil(L);
            lua_pushstring(L, err);
            return 2;
        }
        auxiliar_setclass(L, "udp{connected}", 1);
    } else {
        /* we ignore possible errors because Mac OS X always
         * returns EAFNOSUPPORT */
        inet_trydisconnect(&udp->sock, udp->family, tm);
        auxiliar_setclass(L, "udp{unconnected}", 1);
    }
    /* change class to connected or unconnected depending on address */
    lua_pushnumber(L, 1);
    return 1;
}