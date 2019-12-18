#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int b_abort; int /*<<< orphan*/  thread; int /*<<< orphan*/  lock_out; int /*<<< orphan*/  cond; scalar_t__ b_threaded; } ;
typedef  TYPE_1__ transcode_encoder_t ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  block_ChainAppend (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * transcode_encoder_encode (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * transcode_encoder_get_output_async (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int transcode_encoder_video_drain( transcode_encoder_t *p_enc, block_t **out )
{
    if( !p_enc->b_threaded )
    {
        block_t *p_block;
        do {
            p_block = transcode_encoder_encode( p_enc, NULL );
            block_ChainAppend( out, p_block );
        } while( p_block );
    }
    else
    {
        if( p_enc->b_threaded && !p_enc->b_abort )
        {
            vlc_mutex_lock( &p_enc->lock_out );
            p_enc->b_abort = true;
            vlc_cond_signal( &p_enc->cond );
            vlc_mutex_unlock( &p_enc->lock_out );
            vlc_join( p_enc->thread, NULL );
        }
        block_ChainAppend( out, transcode_encoder_get_output_async( p_enc ) );
    }
    return VLC_SUCCESS;
}