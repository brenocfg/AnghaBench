#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fdc; int /*<<< orphan*/ * fdv; int /*<<< orphan*/ * interrupt; } ;
typedef  TYPE_1__ vlclua_dtable_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaopen_net_intf (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_interrupt_create () ; 
 int /*<<< orphan*/  vlclua_get_dtable ; 
 int /*<<< orphan*/  vlclua_set_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

int vlclua_fd_init( lua_State *L, vlclua_dtable_t *dt )
{
    dt->interrupt = vlc_interrupt_create();
    if( unlikely(dt->interrupt == NULL) )
        return -1;
    dt->fdv = NULL;
    dt->fdc = 0;
    vlclua_set_object( L, vlclua_get_dtable, dt );
    luaopen_net_intf( L );
    return 0;
}