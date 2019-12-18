#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int i_bitspersample; } ;
struct TYPE_10__ {int i_codec; TYPE_2__ audio; } ;
struct TYPE_8__ {int i_codec; } ;
struct TYPE_11__ {int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_packetize; int /*<<< orphan*/  pf_decode; TYPE_3__ fmt_out; TYPE_5__* p_sys; TYPE_1__ fmt_in; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_12__ {int b_packetizer; int i_type; int i_header_size; scalar_t__ i_chans_to_reorder; int /*<<< orphan*/  end_date; } ;
typedef  TYPE_5__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeFrame ; 
 int /*<<< orphan*/  Flush ; 
#define  LPCM_AOB 135 
 int LPCM_AOB_HEADER_LEN ; 
#define  LPCM_BD 134 
 int LPCM_BD_HEADER_LEN ; 
#define  LPCM_VOB 133 
 int LPCM_VOB_HEADER_LEN ; 
#define  LPCM_WIDI 132 
 int LPCM_WIDI_HEADER_LEN ; 
 int /*<<< orphan*/  Packetize ; 
#define  VLC_CODEC_BD_LPCM 131 
#define  VLC_CODEC_DVDA_LPCM 130 
#define  VLC_CODEC_DVD_LPCM 129 
 int VLC_CODEC_S16N ; 
 int VLC_CODEC_S32N ; 
#define  VLC_CODEC_WIDI_LPCM 128 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* malloc (int) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static int OpenCommon( decoder_t *p_dec, bool b_packetizer )
{
    decoder_sys_t *p_sys;
    int i_type;
    int i_header_size;

    switch( p_dec->fmt_in.i_codec )
    {
    /* DVD LPCM */
    case VLC_CODEC_DVD_LPCM:
        i_type = LPCM_VOB;
        i_header_size = LPCM_VOB_HEADER_LEN;
        break;
    /* DVD-Audio LPCM */
    case VLC_CODEC_DVDA_LPCM:
        i_type = LPCM_AOB;
        i_header_size = LPCM_AOB_HEADER_LEN;
        break;
    /* BD LPCM */
    case VLC_CODEC_BD_LPCM:
        i_type = LPCM_BD;
        i_header_size = LPCM_BD_HEADER_LEN;
        break;
    /* WIDI LPCM */
    case VLC_CODEC_WIDI_LPCM:
        i_type = LPCM_WIDI;
        i_header_size = LPCM_WIDI_HEADER_LEN;
        break;
    default:
        return VLC_EGENERIC;
    }

    /* Allocate the memory needed to store the decoder's structure */
    if( ( p_dec->p_sys = p_sys = malloc(sizeof(decoder_sys_t)) ) == NULL )
        return VLC_ENOMEM;

    /* Misc init */
    p_sys->b_packetizer = b_packetizer;
    date_Set( &p_sys->end_date, VLC_TICK_INVALID );
    p_sys->i_type = i_type;
    p_sys->i_header_size = i_header_size;
    p_sys->i_chans_to_reorder = 0;

    /* Set output properties */
    if( b_packetizer )
    {
        switch( i_type )
        {
        case LPCM_VOB:
            p_dec->fmt_out.i_codec = VLC_CODEC_DVD_LPCM;
            break;
        case LPCM_AOB:
            p_dec->fmt_out.i_codec = VLC_CODEC_DVDA_LPCM;
            break;
        case LPCM_WIDI:
            p_dec->fmt_out.i_codec = VLC_CODEC_WIDI_LPCM;
            break;
        default:
            vlc_assert_unreachable();
        case LPCM_BD:
            p_dec->fmt_out.i_codec = VLC_CODEC_BD_LPCM;
            break;
        }
    }
    else
    {
        switch( p_dec->fmt_out.audio.i_bitspersample )
        {
        case 24:
        case 20:
            p_dec->fmt_out.i_codec = VLC_CODEC_S32N;
            p_dec->fmt_out.audio.i_bitspersample = 32;
            break;
        default:
            p_dec->fmt_out.i_codec = VLC_CODEC_S16N;
            p_dec->fmt_out.audio.i_bitspersample = 16;
            break;
        }
    }

    /* Set callback */
    if( !b_packetizer )
        p_dec->pf_decode    = DecodeFrame;
    else
        p_dec->pf_packetize = Packetize;
    p_dec->pf_flush     = Flush;

    return VLC_SUCCESS;
}