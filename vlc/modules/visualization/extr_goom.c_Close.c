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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int b_exit; size_t i_blocks; int /*<<< orphan*/ * pp_blocks; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  p_vout; int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ goom_thread_t ;
struct TYPE_5__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_Close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close( vlc_object_t *p_this )
{
    filter_t     *p_filter = (filter_t *)p_this;
    goom_thread_t *p_thread = p_filter->p_sys;

    /* Stop Goom Thread */
    vlc_mutex_lock( &p_thread->lock );
    p_thread->b_exit = true;
    vlc_cond_signal( &p_thread->wait );
    vlc_mutex_unlock( &p_thread->lock );

    vlc_join( p_thread->thread, NULL );

    /* Free data */
    vout_Close( p_thread->p_vout );
    vlc_mutex_destroy( &p_thread->lock );
    vlc_cond_destroy( &p_thread->wait );

    while( p_thread->i_blocks-- )
    {
        block_Release( p_thread->pp_blocks[p_thread->i_blocks] );
    }

    free( p_thread );
}