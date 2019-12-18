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
typedef  int /*<<< orphan*/ * p_socket ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int,int,char*,int) ; 

__attribute__((used)) static 
int opt_set(lua_State *L, p_socket ps, int level, int name, void *val, int len)
{
    if (setsockopt(*ps, level, name, (char *) val, len) < 0) {
        lua_pushnil(L);
        lua_pushstring(L, "setsockopt failed");
        return 2;
    }
    lua_pushnumber(L, 1);
    return 1;
}