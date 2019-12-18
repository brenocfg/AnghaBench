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
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int vlc_unlink (char const*) ; 

__attribute__((used)) static int vlclua_io_unlink( lua_State *L )
{
    if( lua_gettop( L ) < 1 )
        return luaL_error( L, "Usage: vlc.io.unlink(path)" );
    const char* psz_path = luaL_checkstring( L, 1 );
    int i_res = vlc_unlink( psz_path );
    int i_err = i_res != 0 ? errno : 0;
    lua_pushinteger( L, i_res );
    lua_pushinteger( L, i_err );
    return 2;
}