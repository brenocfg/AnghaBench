#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int b_abort; int /*<<< orphan*/  picture_pool_has_room; int /*<<< orphan*/  cond; TYPE_3__* p_encoder; int /*<<< orphan*/  thread; int /*<<< orphan*/  lock_out; scalar_t__ b_threaded; } ;
typedef  TYPE_1__ transcode_encoder_t ;
struct TYPE_5__ {int /*<<< orphan*/ * p_module; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_unneed (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_destroy (int /*<<< orphan*/ *) ; 

void transcode_encoder_video_close( transcode_encoder_t *p_enc )
{
    if( p_enc->b_threaded && !p_enc->b_abort )
    {
        vlc_mutex_lock( &p_enc->lock_out );
        p_enc->b_abort = true;
        vlc_cond_signal( &p_enc->cond );
        vlc_mutex_unlock( &p_enc->lock_out );
        vlc_join( p_enc->thread, NULL );
    }

    /* Close encoder */
    module_unneed( p_enc->p_encoder, p_enc->p_encoder->p_module );
    p_enc->p_encoder->p_module = NULL;

    vlc_cond_destroy( &p_enc->cond );
    vlc_sem_destroy( &p_enc->picture_pool_has_room );
}