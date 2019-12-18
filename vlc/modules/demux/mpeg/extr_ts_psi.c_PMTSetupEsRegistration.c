#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ const vlc_fourcc_t ;
struct TYPE_9__ {scalar_t__ i_codec; } ;
struct TYPE_8__ {TYPE_2__ fmt; } ;
typedef  TYPE_1__ ts_es_t ;
typedef  TYPE_2__ es_format_t ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;
struct TYPE_10__ {int i_type; } ;
typedef  TYPE_3__ dvbpsi_pmt_es_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
#define  AUDIO_ES 136 
 scalar_t__ PMTEsHasRegistration (int /*<<< orphan*/ *,TYPE_3__ const*,char*) ; 
#define  UNKNOWN_ES 135 
#define  VIDEO_ES 134 
#define  VLC_CODEC_302M 133 
#define  VLC_CODEC_A52 132 
#define  VLC_CODEC_DIRAC 131 
#define  VLC_CODEC_DTS 130 
#define  VLC_CODEC_EAC3 129 
#define  VLC_CODEC_VC1 128 
 int /*<<< orphan*/  es_format_Change (TYPE_2__*,scalar_t__ const,scalar_t__ const) ; 

__attribute__((used)) static bool PMTSetupEsRegistration( demux_t *p_demux, ts_es_t *p_es,
                                    const dvbpsi_pmt_es_t *p_dvbpsies )
{
    static const struct
    {
        char                      psz_tag[5];
        enum es_format_category_e i_cat;
        vlc_fourcc_t              i_codec;
    } p_regs[] = {
        { "AC-3", AUDIO_ES, VLC_CODEC_A52   },
        { "EAC3", AUDIO_ES, VLC_CODEC_EAC3  },
        { "DTS1", AUDIO_ES, VLC_CODEC_DTS   },
        { "DTS2", AUDIO_ES, VLC_CODEC_DTS   },
        { "DTS3", AUDIO_ES, VLC_CODEC_DTS   },
        { "BSSD", AUDIO_ES, VLC_CODEC_302M  },
        { "VC-1", VIDEO_ES, VLC_CODEC_VC1   },
        { "drac", VIDEO_ES, VLC_CODEC_DIRAC },
        { "", UNKNOWN_ES, 0 }
    };
    es_format_t *p_fmt = &p_es->fmt;

    for( int i = 0; p_regs[i].i_cat != UNKNOWN_ES; i++ )
    {
        if( PMTEsHasRegistration( p_demux, p_dvbpsies, p_regs[i].psz_tag ) )
        {
            es_format_Change( p_fmt, p_regs[i].i_cat, p_regs[i].i_codec );

            /* System A AC3 extension, see ATSC A/52 Annex G.2 */
            if ( p_regs[i].i_codec == VLC_CODEC_A52 && p_dvbpsies->i_type == 0x87 )
                p_fmt->i_codec = VLC_CODEC_EAC3;

            return true;
        }
    }
    return false;
}