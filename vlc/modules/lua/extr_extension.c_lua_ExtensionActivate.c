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
typedef  int /*<<< orphan*/  extensions_manager_t ;
typedef  int /*<<< orphan*/  extension_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_END ; 
 int /*<<< orphan*/  assert (int) ; 
 int lua_ExecuteFunction (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int lua_ExtensionActivate( extensions_manager_t *p_mgr, extension_t *p_ext )
{
    assert( p_mgr != NULL && p_ext != NULL );
    return lua_ExecuteFunction( p_mgr, p_ext, "activate", LUA_END );
}