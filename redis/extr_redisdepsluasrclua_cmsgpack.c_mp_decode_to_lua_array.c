#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ err; } ;
typedef  TYPE_1__ mp_cur ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 size_t UINT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_decode_to_lua_type (int /*<<< orphan*/ *,TYPE_1__*) ; 

void mp_decode_to_lua_array(lua_State *L, mp_cur *c, size_t len) {
    assert(len <= UINT_MAX);
    int index = 1;

    lua_newtable(L);
    luaL_checkstack(L, 1, "in function mp_decode_to_lua_array");
    while(len--) {
        lua_pushnumber(L,index++);
        mp_decode_to_lua_type(L,c);
        if (c->err) return;
        lua_settable(L,-3);
    }
}