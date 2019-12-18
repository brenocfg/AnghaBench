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
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 char* vlc_stream_ReadLine (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_stream_readline( lua_State *L )
{
    stream_t **pp_stream = (stream_t **)luaL_checkudata( L, 1, "stream" );
    char *psz_line = vlc_stream_ReadLine( *pp_stream );
    if( psz_line )
    {
        lua_pushstring( L, psz_line );
        free( psz_line );
    }
    else
        lua_pushnil( L );
    return 1;
}