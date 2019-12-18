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
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int net_Accept (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  vlclua_fd_map_safe (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_net_accept( lua_State *L )
{
    vlc_object_t *p_this = vlclua_get_this( L );
    int **ppi_fd = (int**)luaL_checkudata( L, 1, "net_listen" );
    int i_fd = net_Accept( p_this, *ppi_fd );

    lua_pushinteger( L, vlclua_fd_map_safe( L, i_fd ) );
    return 1;
}