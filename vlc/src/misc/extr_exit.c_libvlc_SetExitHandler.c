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
struct TYPE_3__ {void (* handler ) (void*) ;int /*<<< orphan*/  lock; void* opaque; } ;
typedef  TYPE_1__ vlc_exit_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_4__ {TYPE_1__ exit; } ;

/* Variables and functions */
 TYPE_2__* libvlc_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void libvlc_SetExitHandler( libvlc_int_t *p_libvlc, void (*handler) (void *),
                            void *opaque )
{
    vlc_exit_t *exit = &libvlc_priv( p_libvlc )->exit;

    vlc_mutex_lock( &exit->lock );
    exit->handler = handler;
    exit->opaque = opaque;
    vlc_mutex_unlock( &exit->lock );
}