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
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlclua_fd_unmap_safe (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vlclua_net_close( lua_State *L )
{
    int i_fd = luaL_checkinteger( L, 1 );
    vlclua_fd_unmap_safe( L, i_fd );
    return 0;
}