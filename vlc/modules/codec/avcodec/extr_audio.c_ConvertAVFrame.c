#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int i_bytes_per_frame; int /*<<< orphan*/  i_bitspersample; int /*<<< orphan*/  i_channels; int /*<<< orphan*/  i_format; } ;
struct TYPE_18__ {TYPE_1__ audio; } ;
struct TYPE_19__ {TYPE_2__ fmt_out; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_20__ {int /*<<< orphan*/  pi_extraction; scalar_t__ b_extract; TYPE_7__* p_context; } ;
typedef  TYPE_4__ decoder_sys_t ;
struct TYPE_21__ {int i_nb_samples; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_5__ block_t ;
struct TYPE_23__ {int channels; int /*<<< orphan*/  sample_fmt; } ;
struct TYPE_22__ {int* linesize; void** extended_data; int nb_samples; } ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  aout_ChannelExtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aout_Interleave (int /*<<< orphan*/ ,void const**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_6__**) ; 
 scalar_t__ av_sample_fmt_is_planar (int /*<<< orphan*/ ) ; 
 TYPE_5__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_5__*) ; 
 scalar_t__ likely (TYPE_5__*) ; 
 TYPE_5__* vlc_av_frame_Wrap (TYPE_6__*) ; 

__attribute__((used)) static block_t * ConvertAVFrame( decoder_t *p_dec, AVFrame *frame )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    AVCodecContext *ctx = p_sys->p_context;
    block_t *p_block;

    /* Interleave audio if required */
    if( av_sample_fmt_is_planar( ctx->sample_fmt ) )
    {
        p_block = block_Alloc(frame->linesize[0] * ctx->channels);
        if ( likely(p_block) )
        {
            const void *planes[ctx->channels];
            for (int i = 0; i < ctx->channels; i++)
                planes[i] = frame->extended_data[i];

            aout_Interleave(p_block->p_buffer, planes, frame->nb_samples,
                            ctx->channels, p_dec->fmt_out.audio.i_format);
            p_block->i_nb_samples = frame->nb_samples;
        }
        av_frame_free(&frame);
    }
    else
    {
        p_block = vlc_av_frame_Wrap(frame);
        frame = NULL;
    }

    if (p_sys->b_extract && p_block)
    {   /* TODO: do not drop channels... at least not here */
        block_t *p_buffer = block_Alloc( p_dec->fmt_out.audio.i_bytes_per_frame
                                         * p_block->i_nb_samples );
        if( likely(p_buffer) )
        {
            aout_ChannelExtract( p_buffer->p_buffer,
                                 p_dec->fmt_out.audio.i_channels,
                                 p_block->p_buffer, ctx->channels,
                                 p_block->i_nb_samples, p_sys->pi_extraction,
                                 p_dec->fmt_out.audio.i_bitspersample );
            p_buffer->i_nb_samples = p_block->i_nb_samples;
        }
        block_Release( p_block );
        p_block = p_buffer;
    }

    return p_block;
}