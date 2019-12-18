#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  opaque; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ vlc_exit_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_4__ {TYPE_1__ exit; } ;

/* Variables and functions */
 TYPE_2__* libvlc_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void libvlc_Quit( libvlc_int_t *p_libvlc )
{
    vlc_exit_t *exit = &libvlc_priv( p_libvlc )->exit;

    msg_Dbg( p_libvlc, "exiting" );
    vlc_mutex_lock( &exit->lock );
    if( exit->handler != NULL )
        exit->handler( exit->opaque );
    else
        msg_Dbg( p_libvlc, "no exit handler" );
    vlc_mutex_unlock( &exit->lock );
}