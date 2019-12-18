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
typedef  int /*<<< orphan*/  mp_buf ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_encode_lua_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_encode_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

void mp_encode_lua_table_as_map(lua_State *L, mp_buf *buf, int level) {
    size_t len = 0;

    /* First step: count keys into table. No other way to do it with the
     * Lua API, we need to iterate a first time. Note that an alternative
     * would be to do a single run, and then hack the buffer to insert the
     * map opcodes for message pack. Too hackish for this lib. */
    luaL_checkstack(L, 3, "in function mp_encode_lua_table_as_map");
    lua_pushnil(L);
    while(lua_next(L,-2)) {
        lua_pop(L,1); /* remove value, keep key for next iteration. */
        len++;
    }

    /* Step two: actually encoding of the map. */
    mp_encode_map(L,buf,len);
    lua_pushnil(L);
    while(lua_next(L,-2)) {
        /* Stack: ... key value */
        lua_pushvalue(L,-2); /* Stack: ... key value key */
        mp_encode_lua_type(L,buf,level+1); /* encode key */
        mp_encode_lua_type(L,buf,level+1); /* encode val */
    }
}