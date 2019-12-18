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
struct addrinfo {scalar_t__ ai_addrlen; int /*<<< orphan*/  ai_addr; struct addrinfo* ai_next; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  sbuf ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  hbuf ;

/* Variables and functions */
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  getnameinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 char* socket_gaistrerror (int) ; 

__attribute__((used)) static int inet_global_getnameinfo(lua_State *L) {
    char hbuf[NI_MAXHOST];
    char sbuf[NI_MAXSERV];
    int i, ret;
    struct addrinfo hints;
    struct addrinfo *resolved, *iter;
    const char *host = luaL_optstring(L, 1, NULL);
    const char *serv = luaL_optstring(L, 2, NULL);

    if (!(host || serv))
        luaL_error(L, "host and serv cannot be both nil");

    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = PF_UNSPEC;

    ret = getaddrinfo(host, serv, &hints, &resolved);
    if (ret != 0) {
        lua_pushnil(L);
        lua_pushstring(L, socket_gaistrerror(ret));
        return 2;
    }

    lua_newtable(L);
    for (i = 1, iter = resolved; iter; i++, iter = iter->ai_next) {
        getnameinfo(iter->ai_addr, (socklen_t) iter->ai_addrlen, 
            hbuf, host? (socklen_t) sizeof(hbuf): 0, 
            sbuf, serv? (socklen_t) sizeof(sbuf): 0, 0);
        if (host) {
            lua_pushnumber(L, i);
            lua_pushstring(L, hbuf);
            lua_settable(L, -3);
        }
    }
    freeaddrinfo(resolved);

    if (serv) {
        lua_pushstring(L, sbuf);
        return 2;
    } else {
        return 1;
    }
}