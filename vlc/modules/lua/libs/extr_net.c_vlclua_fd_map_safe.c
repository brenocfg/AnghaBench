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
 int /*<<< orphan*/  net_Close (int) ; 
 int vlclua_fd_map (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vlclua_fd_map_safe( lua_State *L, int fd )
{
    int luafd = vlclua_fd_map( L, fd );
    if( luafd == -1 )
        net_Close( fd );
    return luafd;
}