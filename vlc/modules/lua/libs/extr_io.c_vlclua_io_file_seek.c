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
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,long,int) ; 
 int /*<<< orphan*/  ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 long luaL_optinteger (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int vlclua_io_file_seek( lua_State *L )
{
    FILE **pp_file = (FILE**)luaL_checkudata( L, 1, "io_file" );
    if ( !*pp_file )
        return luaL_error( L, "Attempt to use a closed file" );
    const char* psz_mode = luaL_optstring( L, 2, NULL );
    if ( psz_mode != NULL )
    {
        long i_offset = luaL_optinteger( L, 3, 0 );
        int i_mode;
        if ( !strcmp( psz_mode, "set" ) )
            i_mode = SEEK_SET;
        else if ( !strcmp( psz_mode, "end" ) )
            i_mode = SEEK_END;
        else
            i_mode = SEEK_CUR;
        if( fseek( *pp_file, i_offset, i_mode ) != 0 )
            return luaL_error( L, "Failed to seek" );
    }
    lua_pushinteger( L, ftell( *pp_file ) );
    return 1;
}