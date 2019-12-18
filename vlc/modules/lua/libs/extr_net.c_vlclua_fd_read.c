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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int read (int,char*,size_t) ; 
 int vlclua_fd_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlclua_fd_read( lua_State *L )
{
    int fd = vlclua_fd_get( L, luaL_checkinteger( L, 1 ) );
    size_t i_len = (size_t)luaL_optinteger( L, 2, 1 );
    char psz_buffer[i_len];

    ssize_t i_ret = (fd != -1) ? read( fd, psz_buffer, i_len ) : -1;
    if( i_ret > 0 )
        lua_pushlstring( L, psz_buffer, i_ret );
    else
        lua_pushnil( L );
    return 1;
}