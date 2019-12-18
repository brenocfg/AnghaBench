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
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int vlclua_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_vout_internal (int /*<<< orphan*/ *) ; 
 int vlclua_var_toggle_or_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_fullscreen( lua_State *L )
{
    int i_ret;

    vout_thread_t *p_vout = vlclua_get_vout_internal(L);
    if( !p_vout )
        return vlclua_error( L );

    i_ret = vlclua_var_toggle_or_set( L, p_vout, "fullscreen" );

    vout_Release(p_vout);
    return i_ret;
}