#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {double i_frame_rate_base; scalar_t__ i_frame_rate; int /*<<< orphan*/  i_bits_per_pixel; int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; } ;
struct TYPE_15__ {TYPE_7__ video; } ;
struct TYPE_16__ {TYPE_1__ fmt_in; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_17__ {int profile; int level; int /*<<< orphan*/  cc; int /*<<< orphan*/  pix_fmt; TYPE_5__* p_codec; TYPE_4__* p_context; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_19__ {scalar_t__ id; int name; } ;
struct TYPE_18__ {scalar_t__ extradata_size; int active_thread_type; int thread_count; int /*<<< orphan*/  flags; int /*<<< orphan*/  bits_per_coded_sample; int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_4__ AVCodecContext ;
typedef  TYPE_5__ AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_FLAG_LOW_DELAY ; 
 scalar_t__ AV_CODEC_ID_THEORA ; 
 scalar_t__ AV_CODEC_ID_VC1 ; 
 int /*<<< orphan*/  AV_PIX_FMT_NONE ; 
#define  FF_THREAD_FRAME 129 
#define  FF_THREAD_SLICE 128 
 int /*<<< orphan*/  cc_Init (int /*<<< orphan*/ *) ; 
 int ffmpeg_OpenCodec (TYPE_2__*,TYPE_4__*,TYPE_5__ const*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  set_video_color_settings (TYPE_7__*,TYPE_4__*) ; 
 scalar_t__ var_InheritBool (TYPE_2__*,char*) ; 

__attribute__((used)) static int OpenVideoCodec( decoder_t *p_dec )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    AVCodecContext *ctx = p_sys->p_context;
    const AVCodec *codec = p_sys->p_codec;
    int ret;

    if( ctx->extradata_size <= 0 )
    {
        if( codec->id == AV_CODEC_ID_VC1 ||
            codec->id == AV_CODEC_ID_THEORA )
        {
            msg_Warn( p_dec, "waiting for extra data for codec %s",
                      codec->name );
            return 1;
        }
    }

    ctx->width  = p_dec->fmt_in.video.i_visible_width;
    ctx->height = p_dec->fmt_in.video.i_visible_height;

    ctx->coded_width = p_dec->fmt_in.video.i_width;
    ctx->coded_height = p_dec->fmt_in.video.i_height;

    ctx->bits_per_coded_sample = p_dec->fmt_in.video.i_bits_per_pixel;
    p_sys->pix_fmt = AV_PIX_FMT_NONE;
    p_sys->profile = -1;
    p_sys->level = -1;
    cc_Init( &p_sys->cc );

    set_video_color_settings( &p_dec->fmt_in.video, ctx );
    if( p_dec->fmt_in.video.i_frame_rate_base &&
        p_dec->fmt_in.video.i_frame_rate &&
        (double) p_dec->fmt_in.video.i_frame_rate /
                 p_dec->fmt_in.video.i_frame_rate_base < 6 )
    {
        ctx->flags |= AV_CODEC_FLAG_LOW_DELAY;
    }

    if( var_InheritBool(p_dec, "low-delay") )
    {
        ctx->flags |= AV_CODEC_FLAG_LOW_DELAY;
        ctx->active_thread_type = FF_THREAD_SLICE;
    }

    ret = ffmpeg_OpenCodec( p_dec, ctx, codec );
    if( ret < 0 )
        return ret;

    switch( ctx->active_thread_type )
    {
        case FF_THREAD_FRAME:
            msg_Dbg( p_dec, "using frame thread mode with %d threads",
                     ctx->thread_count );
            break;
        case FF_THREAD_SLICE:
            msg_Dbg( p_dec, "using slice thread mode with %d threads",
                     ctx->thread_count );
            break;
        case 0:
            if( ctx->thread_count > 1 )
                msg_Warn( p_dec, "failed to enable threaded decoding" );
            break;
        default:
            msg_Warn( p_dec, "using unknown thread mode with %d threads",
                      ctx->thread_count );
            break;
    }
    return 0;
}