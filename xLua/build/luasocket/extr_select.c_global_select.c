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
typedef  int /*<<< orphan*/  t_timeout ;
typedef  scalar_t__ t_socket ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ SOCKET_INVALID ; 
 int check_dirty (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  collect_fd (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 double luaL_optnumber (int /*<<< orphan*/ *,int,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  make_assoc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  return_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int,int,int) ; 
 int socket_select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout_init (int /*<<< orphan*/ *,double,int) ; 
 int /*<<< orphan*/  timeout_markstart (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int global_select(lua_State *L) {
    int rtab, wtab, itab, ret, ndirty;
    t_socket max_fd = SOCKET_INVALID;
    fd_set rset, wset;
    t_timeout tm;
    double t = luaL_optnumber(L, 3, -1);
    FD_ZERO(&rset); FD_ZERO(&wset);
    lua_settop(L, 3);
    lua_newtable(L); itab = lua_gettop(L);
    lua_newtable(L); rtab = lua_gettop(L);
    lua_newtable(L); wtab = lua_gettop(L);
    collect_fd(L, 1, itab, &rset, &max_fd);
    collect_fd(L, 2, itab, &wset, &max_fd);
    ndirty = check_dirty(L, 1, rtab, &rset);
    t = ndirty > 0? 0.0: t;
    timeout_init(&tm, t, -1);
    timeout_markstart(&tm);
    ret = socket_select(max_fd+1, &rset, &wset, NULL, &tm);
    if (ret > 0 || ndirty > 0) {
        return_fd(L, &rset, max_fd+1, itab, rtab, ndirty);
        return_fd(L, &wset, max_fd+1, itab, wtab, 0);
        make_assoc(L, rtab);
        make_assoc(L, wtab);
        return 2;
    } else if (ret == 0) {
        lua_pushstring(L, "timeout");
        return 3;
    } else {
        luaL_error(L, "select failed");
        return 3;
    }
}