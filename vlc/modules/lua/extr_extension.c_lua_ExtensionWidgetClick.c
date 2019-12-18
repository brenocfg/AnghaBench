#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  extensions_manager_t ;
typedef  int /*<<< orphan*/  extension_widget_t ;
struct TYPE_7__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ extension_t ;
struct TYPE_6__ {int /*<<< orphan*/  L; } ;

/* Variables and functions */
 int /*<<< orphan*/ * GetLuaState (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  LUA_END ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int VLC_SUCCESS ; 
 int lua_ExecuteFunction (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int lua_ExtensionWidgetClick( extensions_manager_t *p_mgr,
                              extension_t *p_ext,
                              extension_widget_t *p_widget )
{
    if( !p_ext->p_sys->L )
        return VLC_SUCCESS;

    lua_State *L = GetLuaState( p_mgr, p_ext );
    lua_pushlightuserdata( L, p_widget );
    lua_gettable( L, LUA_REGISTRYINDEX );
    return lua_ExecuteFunction( p_mgr, p_ext, NULL, LUA_END );
}