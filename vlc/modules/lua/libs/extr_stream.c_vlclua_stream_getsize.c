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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vlc_stream_GetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_stream_getsize( lua_State *L )
{
    stream_t **pp_stream = (stream_t **)luaL_checkudata( L, 1, "stream" );
    uint64_t i_size;
    int i_res = vlc_stream_GetSize( *pp_stream, &i_size );
    if ( i_res != 0 )
        return luaL_error( L, "Failed to get stream size" );
    lua_pushnumber( L, i_size );
    return 1;
}