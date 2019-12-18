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
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * vlc_opendir (char const*) ; 
 char* vlc_readdir (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_opendir( lua_State *L )
{
    const char *psz_dir = luaL_checkstring( L, 1 );
    DIR *p_dir;
    int i = 0;

    if( ( p_dir = vlc_opendir( psz_dir ) ) == NULL )
        return luaL_error( L, "cannot open directory `%s'.", psz_dir );

    lua_newtable( L );
    for( ;; )
    {
        const char *psz_filename = vlc_readdir( p_dir );
        if( !psz_filename ) break;
        i++;
        lua_pushstring( L, psz_filename );
        lua_rawseti( L, -2, i );
    }
    closedir( p_dir );
    return 1;
}