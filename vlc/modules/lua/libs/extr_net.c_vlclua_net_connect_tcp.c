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
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int net_ConnectTCP (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  vlclua_fd_map_safe (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_net_connect_tcp( lua_State *L )
{
    vlc_object_t *p_this = vlclua_get_this( L );
    const char *psz_host = luaL_checkstring( L, 1 );
    int i_port = luaL_checkinteger( L, 2 );
    int i_fd = net_ConnectTCP( p_this, psz_host, i_port );
    lua_pushinteger( L, vlclua_fd_map_safe( L, i_fd ) );
    return 1;
}