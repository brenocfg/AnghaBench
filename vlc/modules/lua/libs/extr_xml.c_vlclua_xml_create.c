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

/* Variables and functions */
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlclua_xml_reg ; 

__attribute__((used)) static int vlclua_xml_create( lua_State *L )
{
    lua_newuserdata( L, 0 );

    if( luaL_newmetatable( L, "xml" ) )
    {
        lua_newtable( L );
        luaL_register( L, NULL, vlclua_xml_reg );
        lua_setfield( L, -2, "__index" );
    }

    lua_setmetatable( L, -2 );
    return 1;
}