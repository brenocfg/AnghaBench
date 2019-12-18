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
struct TYPE_4__ {int /*<<< orphan*/  lock_out; int /*<<< orphan*/  cond; int /*<<< orphan*/  pp_pics; int /*<<< orphan*/  picture_pool_has_room; TYPE_3__* p_encoder; int /*<<< orphan*/  b_threaded; } ;
typedef  TYPE_1__ transcode_encoder_t ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_5__ {int /*<<< orphan*/ * (* pf_encode_video ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  picture_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_fifo_Push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 

block_t * transcode_encoder_video_encode( transcode_encoder_t *p_enc, picture_t *p_pic )
{
    if( !p_enc->b_threaded )
    {
        return p_enc->p_encoder->pf_encode_video( p_enc->p_encoder, p_pic );
    }
    else
    {
        vlc_sem_wait( &p_enc->picture_pool_has_room );
        vlc_mutex_lock( &p_enc->lock_out );
        picture_Hold( p_pic );
        picture_fifo_Push( p_enc->pp_pics, p_pic );
        vlc_cond_signal( &p_enc->cond );
        vlc_mutex_unlock( &p_enc->lock_out );
        return NULL;
    }
}