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
typedef  int /*<<< orphan*/  extension_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_topointer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlclua_extension_set ; 

extension_t *vlclua_extension_get( lua_State *L )
{
    lua_pushlightuserdata( L, vlclua_extension_set );
    lua_rawget( L, LUA_REGISTRYINDEX );
    extension_t *p_ext = (extension_t*) lua_topointer( L, -1 );
    lua_pop( L, 1 );
    return p_ext;
}