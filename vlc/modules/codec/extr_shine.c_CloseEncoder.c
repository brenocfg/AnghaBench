#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ encoder_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_fifo; int /*<<< orphan*/  s; struct TYPE_6__* p_buffer; scalar_t__ i_buffer; } ;
typedef  TYPE_2__ encoder_sys_t ;
struct TYPE_7__ {int busy; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_FifoRelease (int /*<<< orphan*/ ) ; 
 TYPE_4__ entrant ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  shine_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CloseEncoder( vlc_object_t *p_this )
{
    encoder_sys_t *p_sys = ((encoder_t*)p_this)->p_sys;

    vlc_mutex_lock( &entrant.lock );
    entrant.busy = false;
    vlc_mutex_unlock( &entrant.lock );

    /* TODO: we should send the last PCM block padded with 0
     * But we don't know if other blocks will come before it's too late */
    if( p_sys->i_buffer )
        free( p_sys->p_buffer );

    shine_close(p_sys->s);

    block_FifoRelease( p_sys->p_fifo );
    free( p_sys );
}