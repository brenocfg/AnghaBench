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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  stats ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/ * checkstats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ lua_tonumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ stats_value_at (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int script_stats_call(lua_State *L) {
    stats *s = checkstats(L);
    uint64_t index = lua_tonumber(L, 2);
    uint64_t count;
    lua_pushnumber(L, stats_value_at(s, index - 1, &count));
    lua_pushnumber(L, count);
    return 2;
}