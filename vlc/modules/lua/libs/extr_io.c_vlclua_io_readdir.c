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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * vlc_opendir (char const*) ; 
 char* vlc_readdir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_io_readdir( lua_State *L )
{
    if( lua_gettop( L ) < 1 )
        return luaL_error( L, "Usage: vlc.io.readdir(name)" );
    const char* psz_path = luaL_checkstring( L, 1 );
    DIR* p_dir =  vlc_opendir( psz_path );
    if ( p_dir == NULL )
        return 0;

    lua_newtable( L );
    const char* psz_entry;
    int idx = 1;
    while ( ( psz_entry = vlc_readdir( p_dir ) ) != NULL )
    {
        lua_pushstring( L, psz_entry );
        lua_rawseti( L, -2, idx );
        idx++;
    }
    closedir( p_dir );
    return 1;
}