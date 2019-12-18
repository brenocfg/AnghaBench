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
typedef  void* u_short ;
struct linger {void* l_linger; void* l_onoff; } ;
typedef  int /*<<< orphan*/  p_socket ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  li ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_LINGER ; 
 int /*<<< orphan*/  auxiliar_typeerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_toboolean (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int opt_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int opt_set_linger(lua_State *L, p_socket ps)
{
    struct linger li;                      /* obj, name, table */
    if (!lua_istable(L, 3)) auxiliar_typeerror(L,3,lua_typename(L, LUA_TTABLE));
    lua_pushstring(L, "on");
    lua_gettable(L, 3);
    if (!lua_isboolean(L, -1)) 
        luaL_argerror(L, 3, "boolean 'on' field expected");
    li.l_onoff = (u_short) lua_toboolean(L, -1);
    lua_pushstring(L, "timeout");
    lua_gettable(L, 3);
    if (!lua_isnumber(L, -1)) 
        luaL_argerror(L, 3, "number 'timeout' field expected");
    li.l_linger = (u_short) lua_tonumber(L, -1);
    return opt_set(L, ps, SOL_SOCKET, SO_LINGER, (char *) &li, sizeof(li));
}