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
typedef  int t_socket ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int lua_Number ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int FD_SETSIZE ; 
 int /*<<< orphan*/  LUA_TTABLE ; 
 int SOCKET_INVALID ; 
 int getfd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void collect_fd(lua_State *L, int tab, int itab, 
        fd_set *set, t_socket *max_fd) {
    int i = 1, n = 0;
    /* nil is the same as an empty table */
    if (lua_isnil(L, tab)) return;
    /* otherwise we need it to be a table */
    luaL_checktype(L, tab, LUA_TTABLE);
    for ( ;; ) {
        t_socket fd;
        lua_pushnumber(L, i);
        lua_gettable(L, tab);
        if (lua_isnil(L, -1)) {
            lua_pop(L, 1);
            break;
        }
        /* getfd figures out if this is a socket */
        fd = getfd(L);
        if (fd != SOCKET_INVALID) {
            /* make sure we don't overflow the fd_set */
#ifdef _WIN32
            if (n >= FD_SETSIZE) 
                luaL_argerror(L, tab, "too many sockets");
#else
            if (fd >= FD_SETSIZE) 
                luaL_argerror(L, tab, "descriptor too large for set size");
#endif
            FD_SET(fd, set);
            n++;
            /* keep track of the largest descriptor so far */
            if (*max_fd == SOCKET_INVALID || *max_fd < fd) 
                *max_fd = fd;
            /* make sure we can map back from descriptor to the object */
            lua_pushnumber(L, (lua_Number) fd);
            lua_pushvalue(L, -2);
            lua_settable(L, itab);
        }
        lua_pop(L, 1);
        i = i + 1;
    }
}