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
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlclua_stream_delete ; 
 int /*<<< orphan*/  vlclua_stream_reg ; 

__attribute__((used)) static int vlclua_stream_new_inner( lua_State *L, stream_t *p_stream )
{
    if( !p_stream )
    {
        lua_pushnil( L );
        lua_pushliteral( L, "Error when opening stream" );
        return 2;
    }

    stream_t **pp_stream = lua_newuserdata( L, sizeof( stream_t * ) );
    *pp_stream = p_stream;

    if( luaL_newmetatable( L, "stream" ) )
    {
        lua_newtable( L );
        luaL_register( L, NULL, vlclua_stream_reg );
        lua_setfield( L, -2, "__index" );
        lua_pushcfunction( L, vlclua_stream_delete );
        lua_setfield( L, -2, "__gc" );
    }

    lua_setmetatable( L, -2 );
    return 1;
}