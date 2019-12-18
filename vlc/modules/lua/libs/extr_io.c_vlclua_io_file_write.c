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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* LUA_NUMBER_FMT ; 
 scalar_t__ LUA_TNUMBER ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fwrite (char const*,int,size_t,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vlclua_io_file_write( lua_State *L )
{
    FILE **pp_file = (FILE**)luaL_checkudata( L, 1, "io_file" );
    if ( !*pp_file )
        return luaL_error( L, "Attempt to use a closed file" );
    int i_nb_args = lua_gettop( L );
    bool b_success = true;
    for ( int i = 2; i <= i_nb_args; ++i )
    {
        bool i_res;
        if ( lua_type( L, i ) == LUA_TNUMBER )
            i_res = fprintf(*pp_file, LUA_NUMBER_FMT, lua_tonumber( L, i ) ) > 0;
        else
        {
            size_t i_len;
            const char* psz_value = luaL_checklstring( L, i, &i_len );
            i_res = fwrite(psz_value, sizeof(*psz_value), i_len, *pp_file ) > 0;
        }
        b_success = b_success && i_res;
    }
    lua_pushboolean( L, b_success );
    return 1;
}