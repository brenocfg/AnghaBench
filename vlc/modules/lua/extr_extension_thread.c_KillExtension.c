#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  extensions_manager_t ;
struct TYPE_5__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ extension_t ;
struct TYPE_4__ {int b_activated; int b_exiting; int /*<<< orphan*/  wait; int /*<<< orphan*/  dtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_fd_interrupt (int /*<<< orphan*/ *) ; 

void KillExtension( extensions_manager_t *p_mgr, extension_t *p_ext )
{
    msg_Dbg( p_mgr, "Killing extension now" );
    vlclua_fd_interrupt( &p_ext->p_sys->dtable );
    p_ext->p_sys->b_activated = false;
    p_ext->p_sys->b_exiting = true;
    vlc_cond_signal( &p_ext->p_sys->wait );
}