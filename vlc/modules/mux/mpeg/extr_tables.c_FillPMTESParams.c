#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int i_stream_type; int /*<<< orphan*/  i_pid; } ;
typedef  TYPE_5__ tsmux_stream_t ;
typedef  int /*<<< orphan*/  ts_mux_standard ;
struct TYPE_16__ {int i_stream_id; int /*<<< orphan*/  i_es_id; } ;
typedef  TYPE_6__ pesmux_stream_t ;
struct TYPE_13__ {int /*<<< orphan*/  i_id; } ;
struct TYPE_14__ {TYPE_3__ dvb; } ;
struct TYPE_12__ {int i_rate; int i_channels; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_frame_rate_base; int /*<<< orphan*/  i_frame_rate; } ;
struct TYPE_17__ {int i_codec; TYPE_4__ subs; TYPE_2__ audio; TYPE_1__ video; } ;
typedef  TYPE_7__ es_format_t ;

/* Variables and functions */
 int PES_EXTENDED_STREAM_ID ; 
 int /*<<< orphan*/  TS_MUX_STANDARD_ATSC ; 
#define  VLC_CODEC_A52 157 
#define  VLC_CODEC_DIRAC 156 
#define  VLC_CODEC_DIV1 155 
#define  VLC_CODEC_DIV2 154 
#define  VLC_CODEC_DIV3 153 
#define  VLC_CODEC_DTS 152 
#define  VLC_CODEC_DVBS 151 
#define  VLC_CODEC_DVD_LPCM 150 
#define  VLC_CODEC_EAC3 149 
#define  VLC_CODEC_H263 148 
#define  VLC_CODEC_H263I 147 
#define  VLC_CODEC_H264 146 
#define  VLC_CODEC_HEVC 145 
#define  VLC_CODEC_JPEG2000 144 
#define  VLC_CODEC_MJPG 143 
#define  VLC_CODEC_MP1V 142 
#define  VLC_CODEC_MP2 141 
#define  VLC_CODEC_MP2V 140 
#define  VLC_CODEC_MP3 139 
#define  VLC_CODEC_MP4A 138 
#define  VLC_CODEC_MP4V 137 
#define  VLC_CODEC_MPGA 136 
#define  VLC_CODEC_MPGV 135 
#define  VLC_CODEC_OPUS 134 
#define  VLC_CODEC_SPU 133 
#define  VLC_CODEC_SUBT 132 
#define  VLC_CODEC_TELETEXT 131 
#define  VLC_CODEC_WMV1 130 
#define  VLC_CODEC_WMV2 129 
#define  VLC_CODEC_WMV3 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  j2k_is_valid_framerate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int FillPMTESParams( ts_mux_standard standard, const es_format_t *fmt,
                     tsmux_stream_t *ts, pesmux_stream_t *pes )
{
    switch( fmt->i_codec )
    {
    /* VIDEO */

    case VLC_CODEC_MPGV:
    case VLC_CODEC_MP2V:
    case VLC_CODEC_MP1V:
        /* TODO: do we need to check MPEG-I/II ? */
        ts->i_stream_type = 0x02;
        pes->i_stream_id = 0xe0;
        break;
    case VLC_CODEC_MP4V:
        ts->i_stream_type = 0x10;
        pes->i_stream_id = 0xe0;
        pes->i_es_id = ts->i_pid;
        break;
    case VLC_CODEC_HEVC:
        ts->i_stream_type = 0x24;
        pes->i_stream_id = 0xe0;
        break;
    case VLC_CODEC_H264:
        ts->i_stream_type = 0x1b;
        pes->i_stream_id = 0xe0;
        break;
    /* XXX dirty dirty but somebody want crapy MS-codec XXX */
    case VLC_CODEC_H263I:
    case VLC_CODEC_H263:
    case VLC_CODEC_WMV3:
    case VLC_CODEC_WMV2:
    case VLC_CODEC_WMV1:
    case VLC_CODEC_DIV3:
    case VLC_CODEC_DIV2:
    case VLC_CODEC_DIV1:
    case VLC_CODEC_MJPG:
        ts->i_stream_type = 0xa0; /* private */
        pes->i_stream_id = 0xa0;   /* beurk */
        break;
    case VLC_CODEC_DIRAC:
        /* stream_id makes use of stream_id_extension */
        pes->i_stream_id = (PES_EXTENDED_STREAM_ID << 8) | 0x60;
        ts->i_stream_type = 0xd1;
        break;
    case VLC_CODEC_JPEG2000:
        if( !j2k_is_valid_framerate( fmt->video.i_frame_rate,
                                     fmt->video.i_frame_rate_base ) )
            return VLC_EGENERIC;
        ts->i_stream_type = 0x21;
        pes->i_stream_id = 0xbd;
    break;

    /* AUDIO */

    case VLC_CODEC_MPGA:
    case VLC_CODEC_MP2:
    case VLC_CODEC_MP3:
        ts->i_stream_type = fmt->audio.i_rate >= 32000 ? 0x03 : 0x04;
        pes->i_stream_id = 0xc0;
        break;
    case VLC_CODEC_A52:
        pes->i_stream_id = 0xbd;
        if( standard == TS_MUX_STANDARD_ATSC )
        {
            ts->i_stream_type = 0x81;
        }
        else
        {
            ts->i_stream_type = 0x06;
        }
        break;
    case VLC_CODEC_DVD_LPCM:
        ts->i_stream_type = 0x83;
        pes->i_stream_id = 0xbd;
        break;
    case VLC_CODEC_OPUS:
        if (fmt->audio.i_channels > 8)
            return VLC_EGENERIC;
        pes->i_stream_id = 0xbd;
        pes->i_stream_id = 0x06;
        break;
    case VLC_CODEC_EAC3:
        pes->i_stream_id = 0xbd;
        if( standard == TS_MUX_STANDARD_ATSC )
        {
            /* FIXME: Mandatory EAC3 audio_descriptor */
            ts->i_stream_type = 0x87;
        }
        else
        {
            ts->i_stream_type = 0x06;
        }
        break;
    case VLC_CODEC_DTS:
        if( standard == TS_MUX_STANDARD_ATSC )
        {
            return VLC_EGENERIC;
        }
        else
        {
            ts->i_stream_type = 0x06;
            pes->i_stream_id = 0xbd;
        }
        break;
    case VLC_CODEC_MP4A:
        /* XXX: make that configurable in some way when LOAS
         * is implemented for AAC in TS */
        //ts->i_stream_type = 0x11; /* LOAS/LATM */
        ts->i_stream_type = 0x0f; /* ADTS */
        pes->i_stream_id = 0xc0;
        pes->i_es_id = ts->i_pid;
        break;

    /* TEXT */

    case VLC_CODEC_SPU:
        ts->i_stream_type = 0x82;
        pes->i_stream_id = 0xbd;
        break;
    case VLC_CODEC_SUBT:
        ts->i_stream_type = 0x12;
        pes->i_stream_id = 0xfa;
        pes->i_es_id = ts->i_pid;
        break;
    case VLC_CODEC_DVBS:
        ts->i_stream_type = 0x06;
        pes->i_es_id = fmt->subs.dvb.i_id;
        pes->i_stream_id = 0xbd;
        break;
    case VLC_CODEC_TELETEXT:
        ts->i_stream_type = 0x06;
        pes->i_stream_id = 0xbd; /* FIXME */
        break;

    default:
        return VLC_EGENERIC;
    }

    return VLC_SUCCESS;
}