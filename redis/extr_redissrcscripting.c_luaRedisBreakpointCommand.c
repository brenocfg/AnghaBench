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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int luabp; scalar_t__ active; } ;

/* Variables and functions */
 TYPE_1__ ldb ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 

int luaRedisBreakpointCommand(lua_State *lua) {
    if (ldb.active) {
        ldb.luabp = 1;
        lua_pushboolean(lua,1);
    } else {
        lua_pushboolean(lua,0);
    }
    return 1;
}