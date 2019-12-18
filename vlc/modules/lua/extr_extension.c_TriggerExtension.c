#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  extensions_manager_t ;
struct TYPE_6__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ extension_t ;
struct TYPE_5__ {int /*<<< orphan*/ * L; int /*<<< orphan*/  dtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_END ; 
 int lua_ExecuteFunction (int /*<<< orphan*/ *,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_fd_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int TriggerExtension( extensions_manager_t *p_mgr,
                             extension_t *p_ext )
{
    int i_ret = lua_ExecuteFunction( p_mgr, p_ext, "trigger", LUA_END );

    /* Close lua state for trigger-only extensions */
    if( p_ext->p_sys->L )
    {
        vlclua_fd_cleanup( &p_ext->p_sys->dtable );
        lua_close( p_ext->p_sys->L );
    }
    p_ext->p_sys->L = NULL;

    return i_ret;
}