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
typedef  int /*<<< orphan*/  val ;
struct ipv6_mreq {unsigned int ipv6mr_interface; int /*<<< orphan*/  ipv6mr_multiaddr; } ;
typedef  int /*<<< orphan*/  p_socket ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  auxiliar_typeerror (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_pton_w32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ipv6_mreq*,int /*<<< orphan*/ ,int) ; 
 int opt_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char*,int) ; 

__attribute__((used)) static int opt_ip6_setmembership(lua_State *L, p_socket ps, int level, int name)
{
    struct ipv6_mreq val;                   /* obj, opt-name, table */
    memset(&val, 0, sizeof(val));
    if (!lua_istable(L, 3)) auxiliar_typeerror(L,3,lua_typename(L, LUA_TTABLE));
    lua_pushstring(L, "multiaddr");
    lua_gettable(L, 3);
    if (!lua_isstring(L, -1)) 
        luaL_argerror(L, 3, "string 'multiaddr' field expected");
    if (!inet_pton_w32(AF_INET6, lua_tostring(L, -1), &val.ipv6mr_multiaddr)) 
        luaL_argerror(L, 3, "invalid 'multiaddr' ip address");
    lua_pushstring(L, "interface");
    lua_gettable(L, 3);
    /* By default we listen to interface on default route
     * (sigh). However, interface= can override it. We should 
     * support either number, or name for it. Waiting for
     * windows port of if_nametoindex */
    if (!lua_isnil(L, -1)) {
        if (lua_isnumber(L, -1)) {
            val.ipv6mr_interface = (unsigned int) lua_tonumber(L, -1);
        } else
          luaL_argerror(L, -1, "number 'interface' field expected");
    }
    return opt_set(L, ps, level, name, (char *) &val, sizeof(val));
}