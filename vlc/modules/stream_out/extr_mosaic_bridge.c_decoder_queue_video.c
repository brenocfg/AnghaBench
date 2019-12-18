#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {unsigned int i_sar_num; unsigned int i_width; unsigned int i_sar_den; unsigned int i_height; unsigned int i_visible_width; unsigned int i_visible_height; } ;
typedef  TYPE_3__ video_format_t ;
struct decoder_owner {TYPE_4__* p_stream; } ;
struct TYPE_26__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ sout_stream_t ;
struct TYPE_27__ {unsigned int i_height; unsigned int i_width; unsigned int const i_sar_num; unsigned int const i_sar_den; TYPE_7__* p_es; scalar_t__ p_vf2; int /*<<< orphan*/  p_image; scalar_t__ i_chroma; TYPE_2__* p_decoder; } ;
typedef  TYPE_5__ sout_stream_sys_t ;
struct TYPE_28__ {struct TYPE_28__* p_next; TYPE_3__ format; } ;
typedef  TYPE_6__ picture_t ;
typedef  unsigned int int64_t ;
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_29__ {TYPE_6__** pp_last; } ;
typedef  TYPE_7__ bridged_es_t ;
struct TYPE_23__ {TYPE_3__ video; } ;
struct TYPE_24__ {TYPE_1__ fmt_out; } ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_I420 ; 
 int /*<<< orphan*/  VLC_MOSAIC_MUTEX ; 
 unsigned int const VOUT_ASPECT_FACTOR ; 
 struct decoder_owner* dec_get_owner (int /*<<< orphan*/ *) ; 
 TYPE_6__* filter_chain_VideoFilter (scalar_t__,TYPE_6__*) ; 
 TYPE_6__* image_Convert (int /*<<< orphan*/ ,TYPE_6__*,TYPE_3__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  picture_Copy (TYPE_6__*,TYPE_6__*) ; 
 TYPE_6__* picture_NewFromFormat (TYPE_3__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_6__*) ; 
 int /*<<< orphan*/  video_format_Clean (TYPE_3__*) ; 
 int /*<<< orphan*/  video_format_Init (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  vlc_global_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_global_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decoder_queue_video( decoder_t *p_dec, picture_t *p_pic )
{
    struct decoder_owner *p_owner = dec_get_owner( p_dec );
    sout_stream_t *p_stream = p_owner->p_stream;
    sout_stream_sys_t *p_sys = p_stream->p_sys;
    picture_t *p_new_pic;
    const video_format_t *p_fmt_in = &p_sys->p_decoder->fmt_out.video;

    if( p_sys->i_height || p_sys->i_width )
    {
        video_format_t fmt_out;

        video_format_Init( &fmt_out, p_sys->i_chroma ? p_sys->i_chroma : VLC_CODEC_I420 );

        const unsigned i_fmt_in_aspect =
            (int64_t)VOUT_ASPECT_FACTOR *
            p_fmt_in->i_sar_num * p_fmt_in->i_width /
            (p_fmt_in->i_sar_den * p_fmt_in->i_height);
        if ( !p_sys->i_height )
        {
            fmt_out.i_width = p_sys->i_width;
            fmt_out.i_height = (p_sys->i_width * VOUT_ASPECT_FACTOR
                * p_sys->i_sar_num / p_sys->i_sar_den / i_fmt_in_aspect)
                  & ~0x1;
        }
        else if ( !p_sys->i_width )
        {
            fmt_out.i_height = p_sys->i_height;
            fmt_out.i_width = (p_sys->i_height * i_fmt_in_aspect
                * p_sys->i_sar_den / p_sys->i_sar_num / VOUT_ASPECT_FACTOR)
                  & ~0x1;
        }
        else
        {
            fmt_out.i_width = p_sys->i_width;
            fmt_out.i_height = p_sys->i_height;
        }
        fmt_out.i_visible_width = fmt_out.i_width;
        fmt_out.i_visible_height = fmt_out.i_height;

        p_new_pic = image_Convert( p_sys->p_image,
                                   p_pic, p_fmt_in, &fmt_out );
        video_format_Clean( &fmt_out );
        if( p_new_pic == NULL )
        {
            msg_Err( p_stream, "image conversion failed" );
            picture_Release( p_pic );
            return;
        }
    }
    else
    {
        /* TODO: chroma conversion if needed */
        video_format_t pic_fmt = p_pic->format;
        pic_fmt.i_sar_num = p_fmt_in->i_sar_num;
        pic_fmt.i_sar_den = p_fmt_in->i_sar_den;

        p_new_pic = picture_NewFromFormat( &pic_fmt );
        if( !p_new_pic )
        {
            picture_Release( p_pic );
            msg_Err( p_stream, "image allocation failed" );
            return;
        }

        picture_Copy( p_new_pic, p_pic );
    }
    picture_Release( p_pic );

    if( p_sys->p_vf2 )
        p_new_pic = filter_chain_VideoFilter( p_sys->p_vf2, p_new_pic );

    /* push the picture in the mosaic-struct structure */
    bridged_es_t *p_es = p_sys->p_es;
    vlc_global_lock( VLC_MOSAIC_MUTEX );
    *p_es->pp_last = p_new_pic;
    p_new_pic->p_next = NULL;
    p_es->pp_last = &p_new_pic->p_next;
    vlc_global_unlock( VLC_MOSAIC_MUTEX );
}