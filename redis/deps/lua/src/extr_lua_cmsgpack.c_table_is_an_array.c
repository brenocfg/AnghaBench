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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int lua_Integer ;

/* Variables and functions */
 int /*<<< orphan*/  IS_INT_EQUIVALENT (int) ; 
 scalar_t__ LUA_TNUMBER ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

int table_is_an_array(lua_State *L) {
    int count = 0, max = 0;
#if LUA_VERSION_NUM < 503
    lua_Number n;
#else
    lua_Integer n;
#endif

    /* Stack top on function entry */
    int stacktop;

    stacktop = lua_gettop(L);

    lua_pushnil(L);
    while(lua_next(L,-2)) {
        /* Stack: ... key value */
        lua_pop(L,1); /* Stack: ... key */
        /* The <= 0 check is valid here because we're comparing indexes. */
#if LUA_VERSION_NUM < 503
        if ((LUA_TNUMBER != lua_type(L,-1)) || (n = lua_tonumber(L, -1)) <= 0 ||
            !IS_INT_EQUIVALENT(n))
#else
        if (!lua_isinteger(L,-1) || (n = lua_tointeger(L, -1)) <= 0)
#endif
        {
            lua_settop(L, stacktop);
            return 0;
        }
        max = (n > max ? n : max);
        count++;
    }
    /* We have the total number of elements in "count". Also we have
     * the max index encountered in "max". We can't reach this code
     * if there are indexes <= 0. If you also note that there can not be
     * repeated keys into a table, you have that if max==count you are sure
     * that there are all the keys form 1 to count (both included). */
    lua_settop(L, stacktop);
    return max == count;
}