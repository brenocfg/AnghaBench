#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock_out; int /*<<< orphan*/  p_buffers; TYPE_2__* p_encoder; int /*<<< orphan*/  picture_pool_has_room; int /*<<< orphan*/  pp_pics; scalar_t__ b_abort; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ transcode_encoder_t ;
typedef  int /*<<< orphan*/  picture_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_6__ {int /*<<< orphan*/ * (* pf_encode_video ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  block_ChainAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * picture_fifo_Pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub3 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void* EncoderThread( void *obj )
{
    transcode_encoder_t *p_enc = obj;
    picture_t *p_pic = NULL;
    int canc = vlc_savecancel ();
    block_t *p_block = NULL;

    vlc_mutex_lock( &p_enc->lock_out );

    for( ;; )
    {
        while( !p_enc->b_abort &&
               (p_pic = picture_fifo_Pop( p_enc->pp_pics )) == NULL )
            vlc_cond_wait( &p_enc->cond, &p_enc->lock_out );
        vlc_sem_post( &p_enc->picture_pool_has_room );

        if( p_pic )
        {
            /* release lock while encoding */
            vlc_mutex_unlock( &p_enc->lock_out );
            p_block = p_enc->p_encoder->pf_encode_video( p_enc->p_encoder, p_pic );
            picture_Release( p_pic );
            vlc_mutex_lock( &p_enc->lock_out );

            block_ChainAppend( &p_enc->p_buffers, p_block );
        }

        if( p_enc->b_abort )
            break;
    }

    /*Encode what we have in the buffer on closing*/
    while( (p_pic = picture_fifo_Pop( p_enc->pp_pics )) != NULL )
    {
        vlc_sem_post( &p_enc->picture_pool_has_room );
        p_block = p_enc->p_encoder->pf_encode_video( p_enc->p_encoder, p_pic );
        picture_Release( p_pic );
        block_ChainAppend( &p_enc->p_buffers, p_block );
    }

    /*Now flush encoder*/
    do {
        p_block = p_enc->p_encoder->pf_encode_video(p_enc->p_encoder, NULL );
        block_ChainAppend( &p_enc->p_buffers, p_block );
    } while( p_block );

    vlc_mutex_unlock( &p_enc->lock_out );

    vlc_restorecancel (canc);

    return NULL;
}