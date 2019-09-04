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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/ * name; int /*<<< orphan*/  func; } ;
typedef  TYPE_1__ luaL_Reg ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void luaL_setfuncs (lua_State *l, const luaL_Reg *reg, int nup)
{
    int i;

    luaL_checkstack(l, nup, "too many upvalues");
    for (; reg->name != NULL; reg++) {  /* fill the table with given functions */
        for (i = 0; i < nup; i++)  /* copy upvalues to the top */
            lua_pushvalue(l, -nup);
        lua_pushcclosure(l, reg->func, nup);  /* closure with those upvalues */
        lua_setfield(l, -(nup + 2), reg->name);
    }
    lua_pop(l, nup);  /* remove upvalues */
}