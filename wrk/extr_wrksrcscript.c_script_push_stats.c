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
typedef  int /*<<< orphan*/  stats ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 

void script_push_stats(lua_State *L, stats *s) {
    stats **ptr = (stats **) lua_newuserdata(L, sizeof(stats **));
    *ptr = s;
    luaL_getmetatable(L, "wrk.stats");
    lua_setmetatable(L, -2);
}