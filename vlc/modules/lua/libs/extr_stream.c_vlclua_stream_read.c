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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int vlc_stream_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int vlclua_error (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_stream_read( lua_State *L )
{
    int i_read;
    stream_t **pp_stream = (stream_t **)luaL_checkudata( L, 1, "stream" );
    int n = luaL_checkinteger( L, 2 );
    uint8_t *p_read = malloc( n );
    if( !p_read ) return vlclua_error( L );

    i_read = vlc_stream_Read( *pp_stream, p_read, n );
    if( i_read > 0 )
        lua_pushlstring( L, (const char *)p_read, i_read );
    else
        lua_pushnil( L );
    free( p_read );
    return 1;
}