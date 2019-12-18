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
typedef  int /*<<< orphan*/  val ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct ip_mreq {TYPE_1__ imr_interface; TYPE_1__ imr_multiaddr; } ;
typedef  int /*<<< orphan*/  p_socket ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  auxiliar_typeerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_aton (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int opt_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int opt_setmembership(lua_State *L, p_socket ps, int level, int name)
{
    struct ip_mreq val;                   /* obj, name, table */
    if (!lua_istable(L, 3)) auxiliar_typeerror(L,3,lua_typename(L, LUA_TTABLE));
    lua_pushstring(L, "multiaddr");
    lua_gettable(L, 3);
    if (!lua_isstring(L, -1)) 
        luaL_argerror(L, 3, "string 'multiaddr' field expected");
    if (!inet_aton(lua_tostring(L, -1), &val.imr_multiaddr)) 
        luaL_argerror(L, 3, "invalid 'multiaddr' ip address");
    lua_pushstring(L, "interface");
    lua_gettable(L, 3);
    if (!lua_isstring(L, -1)) 
        luaL_argerror(L, 3, "string 'interface' field expected");
    val.imr_interface.s_addr = htonl(INADDR_ANY);
    if (strcmp(lua_tostring(L, -1), "*") &&
            !inet_aton(lua_tostring(L, -1), &val.imr_interface)) 
        luaL_argerror(L, 3, "invalid 'interface' ip address");
    return opt_set(L, ps, level, name, (char *) &val, sizeof(val));
}