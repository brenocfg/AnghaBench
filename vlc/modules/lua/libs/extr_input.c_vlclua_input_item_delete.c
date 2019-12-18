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
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int vlclua_input_item_delete( lua_State *L )
{
    input_item_t **pp_item = luaL_checkudata( L, 1, "input_item" );
    input_item_t *p_item = *pp_item;

    if( !p_item )
        return luaL_error( L, "script went completely foobar" );

    *pp_item = NULL;
    input_item_Release( p_item );

    return 1;
}