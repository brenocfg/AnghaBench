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
 int errno ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vlc_mkdir (char const*,int /*<<< orphan*/ ) ; 
 int vlclua_error (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_mkdir( lua_State *L )
{
    if( lua_gettop( L ) < 2 ) return vlclua_error( L );

    const char* psz_dir = luaL_checkstring( L, 1 );
    const char* psz_mode = luaL_checkstring( L, 2 );
    if ( !psz_dir || !psz_mode )
        return vlclua_error( L );
    int i_res = vlc_mkdir( psz_dir, strtoul( psz_mode, NULL, 0 ) );
    int i_err = i_res != 0 ? errno : 0;
    lua_pushinteger( L, i_res );
    lua_pushinteger( L, i_err );
    return 2;
}