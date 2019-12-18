#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* p_encoder; int /*<<< orphan*/  lock_out; int /*<<< orphan*/  pp_pics; int /*<<< orphan*/  p_buffers; } ;
typedef  TYPE_1__ transcode_encoder_t ;
struct TYPE_8__ {scalar_t__ i_cat; } ;
struct TYPE_7__ {TYPE_5__ fmt_out; TYPE_5__ fmt_in; } ;

/* Variables and functions */
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_5__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  picture_fifo_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_2__*) ; 

void transcode_encoder_delete( transcode_encoder_t *p_enc )
{
    if( p_enc->p_encoder )
    {
        if( p_enc->p_encoder->fmt_in.i_cat == VIDEO_ES )
        {
            block_ChainRelease( p_enc->p_buffers );
            picture_fifo_Delete( p_enc->pp_pics );
            vlc_mutex_destroy( &p_enc->lock_out );
        }
        es_format_Clean( &p_enc->p_encoder->fmt_in );
        es_format_Clean( &p_enc->p_encoder->fmt_out );
        vlc_object_delete(p_enc->p_encoder);
    }
    free( p_enc );
}