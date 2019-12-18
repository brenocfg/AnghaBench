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
struct addrinfo {int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_socktype; } ;
typedef  TYPE_1__* p_tcp ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  bindhints ;
struct TYPE_2__ {int /*<<< orphan*/  sock; int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AI_PASSIVE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  auxiliar_checkclass (int /*<<< orphan*/ *,char*,int) ; 
 char* inet_trybind (int /*<<< orphan*/ *,char const*,char const*,struct addrinfo*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int meth_bind(lua_State *L)
{
    p_tcp tcp = (p_tcp) auxiliar_checkclass(L, "tcp{master}", 1);
    const char *address =  luaL_checkstring(L, 2);
    const char *port = luaL_checkstring(L, 3);
    const char *err;
    struct addrinfo bindhints;
    memset(&bindhints, 0, sizeof(bindhints));
    bindhints.ai_socktype = SOCK_STREAM;
    bindhints.ai_family = tcp->family;
    bindhints.ai_flags = AI_PASSIVE;
    err = inet_trybind(&tcp->sock, address, port, &bindhints);
    if (err) {
        lua_pushnil(L);
        lua_pushstring(L, err);
        return 2;
    }
    lua_pushnumber(L, 1);
    return 1;
}