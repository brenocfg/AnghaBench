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
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 struct addrinfo* luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static struct addrinfo *checkaddr(lua_State *L) {
    struct addrinfo *addr = luaL_checkudata(L, -1, "wrk.addr");
    luaL_argcheck(L, addr != NULL, 1, "`addr' expected");
    return addr;
}