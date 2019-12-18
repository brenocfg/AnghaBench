#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {int i_codec; } ;
typedef  TYPE_1__ es_format_t ;
struct TYPE_13__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_14__ {int /*<<< orphan*/  updates; scalar_t__ p_meta; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_UPDATE_META ; 
 int /*<<< orphan*/  Ogg_ExtractComments (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  Ogg_ExtractFlacComments (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  Ogg_ExtractXiphMeta (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/  const*,int,int) ; 
#define  VLC_CODEC_DAALA 136 
#define  VLC_CODEC_DIRAC 135 
#define  VLC_CODEC_FLAC 134 
#define  VLC_CODEC_KATE 133 
#define  VLC_CODEC_OPUS 132 
#define  VLC_CODEC_SPEEX 131 
#define  VLC_CODEC_THEORA 130 
#define  VLC_CODEC_VORBIS 129 
#define  VLC_CODEC_VP8 128 

__attribute__((used)) static void Ogg_ExtractMeta( demux_t *p_demux, es_format_t *p_fmt, const uint8_t *p_headers, int i_headers )
{
    demux_sys_t *p_ogg = p_demux->p_sys;

    switch( p_fmt->i_codec )
    {
    /* 3 headers with the 2° one being the comments */
    case VLC_CODEC_VORBIS:
    case VLC_CODEC_THEORA:
    case VLC_CODEC_DAALA:
        Ogg_ExtractXiphMeta( p_demux, p_fmt, p_headers, i_headers, 1+6 );
        break;
    case VLC_CODEC_OPUS:
        Ogg_ExtractXiphMeta( p_demux, p_fmt, p_headers, i_headers, 8 );
        break;
    case VLC_CODEC_SPEEX:
        Ogg_ExtractXiphMeta( p_demux, p_fmt, p_headers, i_headers, 0 );
        break;
    case VLC_CODEC_VP8:
        Ogg_ExtractComments( p_demux, p_fmt, p_headers, i_headers );
        break;
    /* N headers with the 2° one being the comments */
    case VLC_CODEC_KATE:
        /* 1 byte for header type, 7 bytes for magic, 1 reserved zero byte */
        Ogg_ExtractXiphMeta( p_demux, p_fmt, p_headers, i_headers, 1+7+1 );
        break;

    /* TODO */
    case VLC_CODEC_FLAC:
        Ogg_ExtractFlacComments( p_demux, p_fmt, p_headers, i_headers );
        break;

    /* No meta data */
    case VLC_CODEC_DIRAC:
    default:
        break;
    }
    if( p_ogg->p_meta )
        p_ogg->updates |= INPUT_UPDATE_META;
}