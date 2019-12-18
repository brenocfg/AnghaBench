#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {scalar_t__ i_codec; int /*<<< orphan*/  i_cat; } ;
struct TYPE_5__ {TYPE_4__ fmt_in; int /*<<< orphan*/  fmt_out; int /*<<< orphan*/ * pf_get_cc; int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_packetize; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_6__ {scalar_t__ i_offset; int /*<<< orphan*/ * p_codec_ctx; int /*<<< orphan*/ * p_parser_ctx; } ;
typedef  TYPE_2__ decoder_sys_t ;
typedef  int /*<<< orphan*/  AVCodecParserContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  FlushPacketizer ; 
 int /*<<< orphan*/  GetFfmpegCodec (int /*<<< orphan*/ ,scalar_t__,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Packetize ; 
 scalar_t__ VLC_CODEC_VP9 ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  av_parser_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_parser_init (unsigned int) ; 
 int /*<<< orphan*/ * avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avcodec_find_decoder (unsigned int) ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  es_format_Copy (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_2__* malloc (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_init_avcodec (int /*<<< orphan*/ *) ; 

int avparser_OpenPacketizer( vlc_object_t *p_this )
{
    decoder_t     *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys;

    /* Restrict to VP9 for now */
    if( p_dec->fmt_in.i_codec != VLC_CODEC_VP9 )
        return VLC_EGENERIC;

    unsigned i_avcodec_id;

    if( !GetFfmpegCodec( p_dec->fmt_in.i_cat, p_dec->fmt_in.i_codec,
                         &i_avcodec_id, NULL ) )
        return VLC_EGENERIC;

    /* init avcodec */
    vlc_init_avcodec(p_this);

    /* It is less likely to have a parser than a codec, start by that */
    AVCodecParserContext * p_ctx = av_parser_init( i_avcodec_id );
    if( !p_ctx )
        return VLC_EGENERIC;

    AVCodec * p_codec = avcodec_find_decoder( i_avcodec_id );
    if( unlikely( !p_codec ) )
    {
        av_parser_close( p_ctx );
        return VLC_EGENERIC;
    }

    AVCodecContext * p_codec_ctx = avcodec_alloc_context3( p_codec );
    if( unlikely( !p_codec_ctx ) )
    {
        av_parser_close( p_ctx );
        return VLC_ENOMEM;
    }

    p_dec->p_sys = p_sys = malloc( sizeof(*p_sys) );

    if( unlikely( !p_sys ) )
    {
        avcodec_free_context( &p_codec_ctx );
        av_parser_close( p_ctx );
        return VLC_ENOMEM;
    }
    p_dec->pf_packetize = Packetize;
    p_dec->pf_flush = FlushPacketizer;
    p_dec->pf_get_cc = NULL;
    p_sys->p_parser_ctx = p_ctx;
    p_sys->p_codec_ctx = p_codec_ctx;
    p_sys->i_offset = 0;
    es_format_Copy( &p_dec->fmt_out, &p_dec->fmt_in );

    return VLC_SUCCESS;
}