#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {scalar_t__ i_cat; int b_packetized; int i_priority; scalar_t__* psz_language; void* i_original_fourcc; } ;
struct TYPE_4__ {int i_skip; int i_id; TYPE_3__ fmt; } ;
typedef  TYPE_1__ ps_track_t ;
typedef  int /*<<< orphan*/  ps_psm_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 scalar_t__ SPU_ES ; 
 scalar_t__ UNKNOWN_ES ; 
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_A52 ; 
 int /*<<< orphan*/  VLC_CODEC_CVD ; 
 int /*<<< orphan*/  VLC_CODEC_DTS ; 
 int /*<<< orphan*/  VLC_CODEC_DVDA_LPCM ; 
 int /*<<< orphan*/  VLC_CODEC_DVD_LPCM ; 
 int /*<<< orphan*/  VLC_CODEC_EAC3 ; 
 int /*<<< orphan*/  VLC_CODEC_H264 ; 
 int /*<<< orphan*/  VLC_CODEC_HEVC ; 
 int /*<<< orphan*/  VLC_CODEC_MLP ; 
 void* VLC_CODEC_MP1V ; 
 int /*<<< orphan*/  VLC_CODEC_MP4A ; 
 int /*<<< orphan*/  VLC_CODEC_MP4V ; 
 int /*<<< orphan*/  VLC_CODEC_MPGA ; 
 int /*<<< orphan*/  VLC_CODEC_MPGV ; 
 int /*<<< orphan*/  VLC_CODEC_OGT ; 
 int /*<<< orphan*/  VLC_CODEC_SPU ; 
 int /*<<< orphan*/  VLC_CODEC_TELETEXT ; 
 int /*<<< orphan*/  VLC_CODEC_TRUEHD ; 
 int /*<<< orphan*/  VLC_CODEC_VC1 ; 
 int VLC_EGENERIC ; 
 void* VLC_FOURCC (char,char,char,char) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  es_format_Change (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 
 scalar_t__ ps_id_to_lang (int /*<<< orphan*/ *,int) ; 
 int ps_id_to_type (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ps_is_H264 (int const*,size_t) ; 

__attribute__((used)) static inline int ps_track_fill( ps_track_t *tk, ps_psm_t *p_psm,
                                 int i_id,
                                 const uint8_t *p_pkt, size_t i_pkt,
                                 bool b_mpeg2only )
{
    tk->i_skip = 0;
    tk->i_id = i_id;

    if( ( i_id&0xff00 ) == 0xbd00 ) /* 0xBD00 -> 0xBDFF, Private Stream 1 */
    {
        if( ( i_id&0xf8 ) == 0x88 || /* 0x88 -> 0x8f - Can be DTS-HD primary audio in evob */
            ( i_id&0xf8 ) == 0x98 )  /* 0x98 -> 0x9f - Can be DTS-HD secondary audio in evob */
        {
            es_format_Change( &tk->fmt, AUDIO_ES, VLC_CODEC_DTS );
            tk->i_skip = 4;
        }
        else if( ( i_id&0xf8 ) == 0x80 || /* 0x80 -> 0x87 */
                 ( i_id&0xf0 ) == 0xc0 )  /* 0xc0 -> 0xcf AC-3, Can also be DD+/E-AC3 in evob */
        {
            bool b_eac3 = false;
            if( ( i_id&0xf0 ) == 0xc0 )
            {
                if( p_pkt == NULL || i_pkt < 9 )
                    return VLC_EGENERIC;

                unsigned i_start = 9 + p_pkt[8];
                if( i_start + 9 < i_pkt )
                {
                    /* AC-3 marking, see vlc_a52_header_Parse */
                    if( p_pkt[i_start + 4] == 0x0b ||
                        p_pkt[i_start + 5] == 0x77 )
                    {
                        int bsid = p_pkt[i_start + 9] >> 3;
                        if( bsid > 10 )
                            b_eac3 = true;
                    }
                }
            }

            es_format_Change( &tk->fmt, AUDIO_ES, b_eac3 ? VLC_CODEC_EAC3 : VLC_CODEC_A52 );
            tk->i_skip = 4;
        }
        else if( ( i_id&0xfc ) == 0x00 ) /* 0x00 -> 0x03 */
        {
            es_format_Change( &tk->fmt, SPU_ES, VLC_CODEC_CVD );
        }
        else if( ( i_id&0xff ) == 0x10 ) /* 0x10 */
        {
            es_format_Change( &tk->fmt, SPU_ES, VLC_CODEC_TELETEXT );
        }
        else if( ( i_id&0xe0 ) == 0x20 ) /* 0x20 -> 0x3f */
        {
            es_format_Change( &tk->fmt, SPU_ES, VLC_CODEC_SPU );
            tk->i_skip = 1;
        }
        else if( ( i_id&0xff ) == 0x70 ) /* 0x70 */
        {
            es_format_Change( &tk->fmt, SPU_ES, VLC_CODEC_OGT );
        }
        else if( ( i_id&0xf0 ) == 0xa0 ) /* 0xa0 -> 0xaf */
        {
            es_format_Change( &tk->fmt, AUDIO_ES, VLC_CODEC_DVD_LPCM );
            tk->i_skip = 1;
        }
        else if( ( i_id&0xf0 ) == 0xb0 ) /* 0xb0 -> 0xbf */
        {
            es_format_Change( &tk->fmt, AUDIO_ES, VLC_CODEC_TRUEHD );
            tk->i_skip = 5;
        }
        else
        {
            es_format_Change( &tk->fmt, UNKNOWN_ES, 0 );
            return VLC_EGENERIC;
        }
    }
    else if( (i_id&0xff00) == 0xfd00 ) /* 0xFD00 -> 0xFDFF */
    {
        uint8_t i_sub_id = i_id & 0xff;
        if( ( i_sub_id >= 0x55 && i_sub_id <= 0x5f ) || /* Can be primary VC-1 in evob */
            ( i_sub_id >= 0x75 && i_sub_id <= 0x7f ) )  /* Secondary VC-1 */
        {
            es_format_Change( &tk->fmt, VIDEO_ES, VLC_CODEC_VC1 );
        }
        else
        {
            es_format_Change( &tk->fmt, UNKNOWN_ES, 0 );
            return VLC_EGENERIC;
        }
    }
    else if( (i_id&0xff00) == 0xa000 ) /* 0xA000 -> 0xA0FF */
    {
        uint8_t i_sub_id = i_id & 0x07;
        if( i_sub_id == 0 )
        {
            es_format_Change( &tk->fmt, AUDIO_ES, VLC_CODEC_DVDA_LPCM );
            tk->i_skip = 1;
        }
        else if( i_sub_id == 1 )
        {
            es_format_Change( &tk->fmt, AUDIO_ES, VLC_CODEC_MLP );
            tk->i_skip = -1; /* It's a hack for variable skip value */
        }
        else
        {
            es_format_Change( &tk->fmt, UNKNOWN_ES, 0 );
            return VLC_EGENERIC;
        }
    }
    else
    {
        int i_type = ps_id_to_type( p_psm , i_id );

        es_format_Change( &tk->fmt, UNKNOWN_ES, 0 );

        if( (i_id&0xf0) == 0xe0 ) /* 0xe0 -> 0xef */
        {
            if( i_type == 0x01 )
            {
                es_format_Change( &tk->fmt, VIDEO_ES, VLC_CODEC_MPGV );
                tk->fmt.i_original_fourcc = VLC_CODEC_MP1V;
            }
            else if( i_type == 0x02 )
            {
                es_format_Change( &tk->fmt, VIDEO_ES, VLC_CODEC_MPGV );
            }
            else if( i_type == 0x10 )
            {
                es_format_Change( &tk->fmt, VIDEO_ES, VLC_CODEC_MP4V );
            }
            else if( i_type == 0x1b )
            {
                es_format_Change( &tk->fmt, VIDEO_ES, VLC_CODEC_H264 );
            }
            else if( i_type == 0x24 )
            {
                es_format_Change( &tk->fmt, VIDEO_ES, VLC_CODEC_HEVC );
            }
            else if( i_id == 0xe2 || /* Primary H.264 in evob */
                     i_id == 0xe3 )  /* Seconday H.264 in evob */
            {
                es_format_Change( &tk->fmt, VIDEO_ES, VLC_CODEC_H264 );
            }
            else if( p_pkt && i_type == 0x00 && /* Not from PSM */
                     i_pkt > 9 + 5 &&
                     i_pkt > 9U + 5 + p_pkt[8] &&
                     ps_is_H264( &p_pkt[ 9 + p_pkt[8] ],
                                  i_pkt - 9 - p_pkt[8] ) )
            {
                es_format_Change( &tk->fmt, VIDEO_ES, VLC_CODEC_H264 );
            }
            else if( tk->fmt.i_cat == UNKNOWN_ES &&
                     ( p_pkt != NULL /* Not system */ || b_mpeg2only ) )
            {
                es_format_Change( &tk->fmt, VIDEO_ES, VLC_CODEC_MPGV );
            }
        }
        else if( ( i_id&0xe0 ) == 0xc0 ) /* 0xc0 -> 0xdf */
        {
            if( i_type == 0x03 ||
                i_type == 0x04 )
            {
                es_format_Change( &tk->fmt, AUDIO_ES, VLC_CODEC_MPGA );
            }
            else if( i_type == 0x0f )
            {
                es_format_Change( &tk->fmt, AUDIO_ES, VLC_CODEC_MP4A );
                tk->fmt.i_original_fourcc = VLC_FOURCC('A','D','T','S');
            }
            else if( i_type == 0x11 )
            {
                es_format_Change( &tk->fmt, AUDIO_ES, VLC_CODEC_MP4A );
                tk->fmt.i_original_fourcc = VLC_FOURCC('L','A','T','M');
            }
            else if( tk->fmt.i_cat == UNKNOWN_ES )
            {
                es_format_Change( &tk->fmt, AUDIO_ES, VLC_CODEC_MPGA );
            }
        }
        else if( tk->fmt.i_cat == UNKNOWN_ES ) return VLC_EGENERIC;
    }

    /* PES packets usually contain truncated frames */
    tk->fmt.b_packetized = false;
    tk->fmt.i_priority = ~i_id & 0x0F;

    if( ps_id_to_lang( p_psm, i_id ) )
    {
        tk->fmt.psz_language = malloc( 4 );
        if( tk->fmt.psz_language )
        {
            memcpy( tk->fmt.psz_language, ps_id_to_lang( p_psm , i_id ), 3 );
            tk->fmt.psz_language[3] = 0;
        }
    }

    return (tk->fmt.i_cat != UNKNOWN_ES || p_pkt) ? VLC_SUCCESS : VLC_EGENERIC;
}