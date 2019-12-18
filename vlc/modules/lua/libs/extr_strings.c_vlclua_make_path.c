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
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 char* vlc_uri2path (char const*) ; 

__attribute__((used)) static int vlclua_make_path( lua_State *L )
{
    const char *psz_input = luaL_checkstring( L, 1 );
    char *psz_path = vlc_uri2path( psz_input);
    lua_pushstring( L, psz_path );
    free( psz_path );
    return 1;
}