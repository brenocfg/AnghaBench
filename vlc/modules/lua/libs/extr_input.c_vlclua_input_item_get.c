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
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_item_Hold (int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlclua_input_item_delete ; 
 int /*<<< orphan*/  vlclua_input_item_reg ; 

int vlclua_input_item_get( lua_State *L, input_item_t *p_item )
{
    input_item_Hold( p_item );
    input_item_t **pp = lua_newuserdata( L, sizeof( input_item_t* ) );
    *pp = p_item;

    if( luaL_newmetatable( L, "input_item" ) )
    {
        lua_newtable( L );
        luaL_register( L, NULL, vlclua_input_item_reg );
        lua_setfield( L, -2, "__index" );
        lua_pushcfunction( L, vlclua_input_item_delete );
        lua_setfield( L, -2, "__gc" );
    }

    lua_setmetatable(L, -2);

    return 1;
}