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

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_optinteger (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int vlc_write (int,char const*,size_t) ; 
 int vlclua_fd_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlclua_fd_write( lua_State *L )
{
    int fd = vlclua_fd_get( L, luaL_checkinteger( L, 1 ) );
    size_t i_len;
    const char *psz_buffer = luaL_checklstring( L, 2, &i_len );

    i_len = (size_t)luaL_optinteger( L, 3, i_len );
    lua_pushinteger( L, (fd != -1) ? vlc_write( fd, psz_buffer, i_len ) : -1 );
    return 1;
}