#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  interrupt; } ;
typedef  TYPE_1__ vlclua_dtable_t ;
typedef  int /*<<< orphan*/  vlc_interrupt_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/ * vlc_interrupt_set (int /*<<< orphan*/ ) ; 
 TYPE_1__* vlclua_get_dtable (int /*<<< orphan*/ *) ; 

vlc_interrupt_t *vlclua_set_interrupt( lua_State *L )
{
    vlclua_dtable_t *dt = vlclua_get_dtable( L );
    return vlc_interrupt_set( dt->interrupt );
}