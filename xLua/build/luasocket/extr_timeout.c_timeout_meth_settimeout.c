#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* p_timeout ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {double block; double total; } ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 double luaL_optnumber (int /*<<< orphan*/ *,int,int) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 

int timeout_meth_settimeout(lua_State *L, p_timeout tm) {
    double t = luaL_optnumber(L, 2, -1);
    const char *mode = luaL_optstring(L, 3, "b");
    switch (*mode) {
        case 'b':
            tm->block = t; 
            break;
        case 'r': case 't':
            tm->total = t;
            break;
        default:
            luaL_argcheck(L, 0, 3, "invalid timeout mode");
            break;
    }
    lua_pushnumber(L, 1);
    return 1;
}