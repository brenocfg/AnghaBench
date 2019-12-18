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
struct TYPE_8__ {int /*<<< orphan*/  i_profile; } ;
struct TYPE_7__ {TYPE_2__ fmt; } ;
typedef  TYPE_1__ ts_es_t ;
typedef  TYPE_2__ es_format_t ;
struct TYPE_9__ {int i_type; int /*<<< orphan*/  i_pid; } ;
typedef  TYPE_3__ dvbpsi_pmt_es_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  PROFILE_DTS_HD ; 
 int /*<<< orphan*/  SPU_ES ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_A52 ; 
 int /*<<< orphan*/  VLC_CODEC_BD_LPCM ; 
 int /*<<< orphan*/  VLC_CODEC_BD_PG ; 
 int /*<<< orphan*/  VLC_CODEC_BD_TEXT ; 
 int /*<<< orphan*/  VLC_CODEC_DTS ; 
 int /*<<< orphan*/  VLC_CODEC_EAC3 ; 
 int /*<<< orphan*/  VLC_CODEC_TRUEHD ; 
 int /*<<< orphan*/  VLC_CODEC_VC1 ; 
 int /*<<< orphan*/  es_format_Change (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool PMTSetupEsHDMV( demux_t *p_demux, ts_es_t *p_es,
                            const dvbpsi_pmt_es_t *p_dvbpsies )
{
    es_format_t *p_fmt = &p_es->fmt;

    /* Blu-Ray mapping */
    switch( p_dvbpsies->i_type )
    {
    case 0x80:
        es_format_Change( p_fmt, AUDIO_ES, VLC_CODEC_BD_LPCM );
        break;
    case 0x81:
        es_format_Change( p_fmt, AUDIO_ES, VLC_CODEC_A52 );
        break;
    case 0x85: /* DTS-HD High resolution audio */
    case 0x86: /* DTS-HD Master audio */
        es_format_Change( p_fmt, AUDIO_ES, VLC_CODEC_DTS );
        p_fmt->i_profile = PROFILE_DTS_HD;
        break;
    case 0x82:
    case 0xA2: /* Secondary DTS audio */
        es_format_Change( p_fmt, AUDIO_ES, VLC_CODEC_DTS );
        break;

    case 0x83: /* TrueHD AC3 */
        es_format_Change( p_fmt, AUDIO_ES, VLC_CODEC_TRUEHD );
        break;

    case 0x84: /* E-AC3 */
    case 0xA1: /* Secondary E-AC3 */
        es_format_Change( p_fmt, AUDIO_ES, VLC_CODEC_EAC3 );
        break;
    case 0x90: /* Presentation graphics */
        es_format_Change( p_fmt, SPU_ES, VLC_CODEC_BD_PG );
        break;
    case 0x91: /* Interactive graphics */
        return false;
    case 0x92: /* Subtitle */
        es_format_Change( p_fmt, SPU_ES, VLC_CODEC_BD_TEXT );
        break;
    case 0xEA:
        es_format_Change( p_fmt, VIDEO_ES, VLC_CODEC_VC1 );
        break;
    default:
        msg_Info( p_demux, "HDMV registration not implemented for pid 0x%x type 0x%x",
                  p_dvbpsies->i_pid, p_dvbpsies->i_type );
        return false;
    }
    return true;
}