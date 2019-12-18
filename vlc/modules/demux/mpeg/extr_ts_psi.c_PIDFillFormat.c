#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ts_transport_type_t ;
struct TYPE_8__ {int /*<<< orphan*/  p_sections_proc; TYPE_1__* p_es; } ;
typedef  TYPE_2__ ts_stream_t ;
struct TYPE_9__ {void* i_original_fourcc; } ;
typedef  TYPE_3__ es_format_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_7__ {TYPE_3__ fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  SCTE27_Section_Callback ; 
 int /*<<< orphan*/  SPU_ES ; 
 int /*<<< orphan*/  TS_TRANSPORT_SECTIONS ; 
 int /*<<< orphan*/  UNKNOWN_ES ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 void* VLC_CODEC_A52 ; 
 void* VLC_CODEC_CAVS ; 
 void* VLC_CODEC_DTS ; 
 void* VLC_CODEC_EAC3 ; 
 void* VLC_CODEC_H264 ; 
 void* VLC_CODEC_HEVC ; 
 void* VLC_CODEC_MP1V ; 
 void* VLC_CODEC_MP4A ; 
 void* VLC_CODEC_MP4V ; 
 void* VLC_CODEC_MPGA ; 
 void* VLC_CODEC_MPGV ; 
 void* VLC_CODEC_SCTE_27 ; 
 void* VLC_CODEC_SDDS ; 
 void* VLC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  es_format_Change (TYPE_3__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ts_sections_processor_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void PIDFillFormat( demux_t *p_demux, ts_stream_t *p_pes,
                           int i_stream_type, ts_transport_type_t *p_datatype )
{
    es_format_t *fmt = &p_pes->p_es->fmt;
    switch( i_stream_type )
    {
    case 0x01:  /* MPEG-1 video */
        es_format_Change( fmt, VIDEO_ES, VLC_CODEC_MPGV );
        fmt->i_original_fourcc = VLC_CODEC_MP1V;
        break;
    case 0x02:  /* MPEG-2 video */
    case 0x80:  /* MPEG-2 MOTO video */
        es_format_Change( fmt, VIDEO_ES, VLC_CODEC_MPGV );
        break;
    case 0x03:  /* MPEG-1 audio */
    case 0x04:  /* MPEG-2 audio */
        es_format_Change( fmt, AUDIO_ES, VLC_CODEC_MPGA );
        break;
    case 0x0f:  /* ISO/IEC 13818-7 Audio with ADTS transport syntax */
        es_format_Change( fmt, AUDIO_ES, VLC_CODEC_MP4A );
        fmt->i_original_fourcc = VLC_FOURCC('A','D','T','S');
        break;
    case 0x10:  /* MPEG4 (video) */
        es_format_Change( fmt, VIDEO_ES, VLC_CODEC_MP4V );
        break;
    case 0x11:  /* MPEG4 (audio) LATM */
        es_format_Change( fmt, AUDIO_ES, VLC_CODEC_MP4A );
        fmt->i_original_fourcc = VLC_FOURCC('L','A','T','M');
        break;
    case 0x1B:  /* H264 <- check transport syntax/needed descriptor */
        es_format_Change( fmt, VIDEO_ES, VLC_CODEC_H264 );
        break;
    case 0x1C:  /* ISO/IEC 14496-3 Audio, without using any additional
                   transport syntax, such as DST, ALS and SLS */
        es_format_Change( fmt, AUDIO_ES, VLC_CODEC_MP4A );
        break;
    case 0x24:  /* HEVC */
        es_format_Change( fmt, VIDEO_ES, VLC_CODEC_HEVC );
        break;
    case 0x42:  /* CAVS (Chinese AVS) */
        es_format_Change( fmt, VIDEO_ES, VLC_CODEC_CAVS );
        break;

    case 0x81:  /* A52 (audio) */
        es_format_Change( fmt, AUDIO_ES, VLC_CODEC_A52 );
        break;
    case 0x82:  /* SCTE-27 (sub) */
        es_format_Change( fmt, SPU_ES, VLC_CODEC_SCTE_27 );
        *p_datatype = TS_TRANSPORT_SECTIONS;
        ts_sections_processor_Add( p_demux, &p_pes->p_sections_proc, 0xC6, 0x00,
                                   SCTE27_Section_Callback, p_pes );
        break;
    case 0x84:  /* SDDS (audio) */
        es_format_Change( fmt, AUDIO_ES, VLC_CODEC_SDDS );
        break;
    case 0x85:  /* DTS (audio) FIXME: HDMV Only ? */
        es_format_Change( fmt, AUDIO_ES, VLC_CODEC_DTS );
        break;
    case 0x87: /* E-AC3, ATSC */
        es_format_Change( fmt, AUDIO_ES, VLC_CODEC_EAC3 );
        break;
    case 0x8a: /* DTS (audio) */
        es_format_Change( fmt, AUDIO_ES, VLC_CODEC_DTS );
        break;
    case 0x91:  /* A52 vls (audio) */
        es_format_Change( fmt, AUDIO_ES, VLC_FOURCC( 'a', '5', '2', 'b' ) );
        break;
    case 0x92:  /* DVD_SPU vls (sub) */
        es_format_Change( fmt, SPU_ES, VLC_FOURCC( 's', 'p', 'u', 'b' ) );
        break;

    case 0x94:  /* SDDS (audio) */
        es_format_Change( fmt, AUDIO_ES, VLC_FOURCC( 's', 'd', 'd', 'b' ) );
        break;

    case 0xa0:  /* MSCODEC vlc (video) (fixed later) */
        es_format_Change( fmt, UNKNOWN_ES, 0 );
        break;

    case 0x06:  /* PES_PRIVATE  (fixed later) */
    case 0x12:  /* MPEG-4 generic (sub/scene/...) (fixed later) */
    case 0xEA:  /* Privately managed ES (VC-1) (fixed later */
    default:
        es_format_Change( fmt, UNKNOWN_ES, 0 );
        break;
    }
}