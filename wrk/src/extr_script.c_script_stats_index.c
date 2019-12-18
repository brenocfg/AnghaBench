#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
typedef  TYPE_1__ stats ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 TYPE_1__* checkstats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  script_stats_percentile ; 
 int /*<<< orphan*/  stats_mean (TYPE_1__*) ; 
 int /*<<< orphan*/  stats_stdev (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static int script_stats_index(lua_State *L) {
    stats *s = checkstats(L);
    const char *method = lua_tostring(L, 2);
    if (!strcmp("min",   method)) lua_pushnumber(L, s->min);
    if (!strcmp("max",   method)) lua_pushnumber(L, s->max);
    if (!strcmp("mean",  method)) lua_pushnumber(L, stats_mean(s));
    if (!strcmp("stdev", method)) lua_pushnumber(L, stats_stdev(s, stats_mean(s)));
    if (!strcmp("percentile", method)) {
        lua_pushcfunction(L, script_stats_percentile);
    }
    return 1;
}