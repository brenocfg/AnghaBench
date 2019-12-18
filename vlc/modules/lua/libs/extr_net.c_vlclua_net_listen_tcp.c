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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*,int) ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  net_ListenClose (int*) ; 
 int* net_ListenTCP (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  vlclua_fd_get_lua (int /*<<< orphan*/ *,int) ; 
 int vlclua_fd_map (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlclua_fd_unmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_net_listen_close ; 
 int /*<<< orphan*/  vlclua_net_listen_reg ; 

__attribute__((used)) static int vlclua_net_listen_tcp( lua_State *L )
{
    vlc_object_t *p_this = vlclua_get_this( L );
    const char *psz_host = luaL_checkstring( L, 1 );
    int i_port = luaL_checkinteger( L, 2 );
    int *pi_fd = net_ListenTCP( p_this, psz_host, i_port );
    if( pi_fd == NULL )
        return luaL_error( L, "Cannot listen on %s:%d", psz_host, i_port );

    for( unsigned i = 0; pi_fd[i] != -1; i++ )
        if( vlclua_fd_map( L, pi_fd[i] ) == -1 )
        {
            while( i > 0 )
                vlclua_fd_unmap( L, vlclua_fd_get_lua( L, pi_fd[--i] ) );

            net_ListenClose( pi_fd );
            return luaL_error( L, "Cannot listen on %s:%d", psz_host, i_port );
        }

    int **ppi_fd = lua_newuserdata( L, sizeof( int * ) );
    *ppi_fd = pi_fd;

    if( luaL_newmetatable( L, "net_listen" ) )
    {
        lua_newtable( L );
        luaL_register( L, NULL, vlclua_net_listen_reg );
        lua_setfield( L, -2, "__index" );
        lua_pushcfunction( L, vlclua_net_listen_close );
        lua_setfield( L, -2, "__gc" );
    }

    lua_setmetatable( L, -2 );
    return 1;
}