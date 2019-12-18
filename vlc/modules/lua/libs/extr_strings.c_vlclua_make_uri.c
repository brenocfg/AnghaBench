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
 int /*<<< orphan*/  free (char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 
 char* vlc_path2uri (char const*,char const*) ; 

__attribute__((used)) static int vlclua_make_uri( lua_State *L )
{
    const char *psz_input = luaL_checkstring( L, 1 );
    const char *psz_scheme = luaL_optstring( L, 2, NULL );
    if( strstr( psz_input, "://" ) == NULL )
    {
        char *psz_uri = vlc_path2uri( psz_input, psz_scheme );
        lua_pushstring( L, psz_uri );
        free( psz_uri );
    }
    else
        lua_pushstring( L, psz_input );
    return 1;
}