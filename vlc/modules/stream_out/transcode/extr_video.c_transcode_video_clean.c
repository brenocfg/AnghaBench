#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sout_stream_t ;
struct TYPE_3__ {scalar_t__ p_spu; scalar_t__ p_spu_blender; int /*<<< orphan*/  p_final_conv_static; int /*<<< orphan*/  p_uf_chain; int /*<<< orphan*/  p_conv_static; int /*<<< orphan*/  p_conv_nonstatic; int /*<<< orphan*/  p_f_chain; int /*<<< orphan*/  decoder_out; int /*<<< orphan*/  fmt_input_video; int /*<<< orphan*/  encoder; } ;
typedef  TYPE_1__ sout_stream_id_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_DeleteBlend (scalar_t__) ; 
 int /*<<< orphan*/  spu_Destroy (scalar_t__) ; 
 int /*<<< orphan*/  transcode_encoder_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transcode_encoder_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transcode_remove_filters (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 

void transcode_video_clean( sout_stream_t *p_stream,
                                   sout_stream_id_sys_t *id )
{
    VLC_UNUSED(p_stream);

    /* Close encoder */
    transcode_encoder_close( id->encoder );
    transcode_encoder_delete( id->encoder );

    video_format_Clean( &id->fmt_input_video );
    es_format_Clean( &id->decoder_out );

    /* Close filters */
    transcode_remove_filters( &id->p_f_chain );
    transcode_remove_filters( &id->p_conv_nonstatic );
    transcode_remove_filters( &id->p_conv_static );
    transcode_remove_filters( &id->p_uf_chain );
    transcode_remove_filters( &id->p_final_conv_static );
    if( id->p_spu_blender )
        filter_DeleteBlend( id->p_spu_blender );
    if( id->p_spu )
        spu_Destroy( id->p_spu );
}