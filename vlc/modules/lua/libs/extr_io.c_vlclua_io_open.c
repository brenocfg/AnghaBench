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
typedef  int /*<<< orphan*/  p_f ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vlc_fopen (char const*,char const*) ; 
 int /*<<< orphan*/  vlclua_io_file_close ; 
 int /*<<< orphan*/  vlclua_io_file_reg ; 

__attribute__((used)) static int vlclua_io_open( lua_State *L )
{
    if( lua_gettop( L ) < 1 )
        return luaL_error( L, "Usage: vlc.io.open(file_path [, mode])" );
    const char* psz_path = luaL_checkstring( L, 1 );
    const char* psz_mode = luaL_optstring( L, 2, "r" );
    FILE *p_f =  vlc_fopen( psz_path, psz_mode );
    if ( p_f == NULL )
        return 0;

    FILE** pp_f = lua_newuserdata( L, sizeof( p_f ) );
    *pp_f = p_f;

    if( luaL_newmetatable( L, "io_file" ) )
    {
        lua_newtable( L );
        luaL_register( L, NULL, vlclua_io_file_reg );
        lua_setfield( L, -2, "__index" );
        lua_pushcfunction( L, vlclua_io_file_close );
        lua_setfield( L, -2, "__gc" );
    }
    lua_setmetatable( L, -2 );
    return 1;
}