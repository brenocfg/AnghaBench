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
typedef  int /*<<< orphan*/  vlc_interrupt_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  llround (double) ; 
 double luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_interrupt_set (int /*<<< orphan*/ *) ; 
 int vlc_mwait_i11e (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlclua_set_interrupt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_mwait( lua_State *L )
{
    double f = luaL_checknumber( L, 1 );

    vlc_interrupt_t *oint = vlclua_set_interrupt( L );
    int ret = vlc_mwait_i11e( llround(f) );

    vlc_interrupt_set( oint );
    if( ret )
        return luaL_error( L, "Interrupted." );
    return 0;
}