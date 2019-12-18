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
 scalar_t__ LUA_TNUMBER ; 
 size_t SIZE_MAX ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int vlclua_io_file_read_chars (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int vlclua_io_file_read_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlclua_io_file_read_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_io_file_read( lua_State *L )
{
    FILE **pp_file = (FILE**)luaL_checkudata( L, 1, "io_file" );
    if ( !*pp_file )
        return luaL_error( L, "Attempt to use a closed file" );
    if( lua_type( L, 2 ) == LUA_TNUMBER )
    {
        return vlclua_io_file_read_chars( L, (size_t)lua_tointeger( L, 2 ),
                                          *pp_file );
    }
    const char* psz_mode = luaL_optstring( L, 2, "*l" );
    if ( *psz_mode != '*' )
        return luaL_error( L, "Invalid file:read() format: %s", psz_mode );
    switch ( psz_mode[1] )
    {
        case 'l':
            return vlclua_io_file_read_line( L, *pp_file );
        case 'n':
            return vlclua_io_file_read_number( L, *pp_file );
        case 'a':
            return vlclua_io_file_read_chars( L, SIZE_MAX, *pp_file );
        default:
            break;
    }
    return luaL_error( L, "Invalid file:read() format: %s", psz_mode );
}