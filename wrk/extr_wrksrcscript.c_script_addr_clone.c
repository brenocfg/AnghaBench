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
struct addrinfo {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 struct addrinfo* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  script_addr_copy (struct addrinfo*,struct addrinfo*) ; 

struct addrinfo *script_addr_clone(lua_State *L, struct addrinfo *addr) {
    struct addrinfo *udata = lua_newuserdata(L, sizeof(*udata));
    luaL_getmetatable(L, "wrk.addr");
    lua_setmetatable(L, -2);
    script_addr_copy(addr, udata);
    return udata;
}