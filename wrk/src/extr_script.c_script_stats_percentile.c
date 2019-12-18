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
typedef  int /*<<< orphan*/  lua_Number ;

/* Variables and functions */
 int /*<<< orphan*/ * checkstats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_percentile (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int script_stats_percentile(lua_State *L) {
    stats *s = checkstats(L);
    lua_Number p = luaL_checknumber(L, 2);
    lua_pushnumber(L, stats_percentile(s, p));
    return 1;
}