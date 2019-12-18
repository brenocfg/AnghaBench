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
typedef  int lua_Integer ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 
 char* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_rand_bytes (char*,int) ; 
 int vlclua_error (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_rand_bytes( lua_State *L )
{
    lua_Integer i_size = luaL_checkinteger( L, 1 );
    char* p_buff = malloc( i_size * sizeof( *p_buff ) );
    if ( unlikely( p_buff == NULL ) )
        return vlclua_error( L );
    vlc_rand_bytes( p_buff, i_size );
    lua_pushlstring( L, p_buff, i_size );
    free( p_buff );
    return 1;
}