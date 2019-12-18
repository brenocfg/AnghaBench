#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_32__ {TYPE_1__* p_es; } ;
typedef  TYPE_3__ ts_stream_t ;
struct TYPE_33__ {int b_packetized; scalar_t__ i_cat; void* psz_description; void* psz_language; int /*<<< orphan*/  i_profile; } ;
typedef  TYPE_4__ es_format_t ;
struct TYPE_34__ {int i_subtitles_number; TYPE_2__* p_subtitle; } ;
typedef  TYPE_5__ dvbpsi_subtitling_dr_t ;
struct TYPE_35__ {int /*<<< orphan*/  i_component_tag; } ;
typedef  TYPE_6__ dvbpsi_stream_identifier_dr_t ;
typedef  int /*<<< orphan*/  dvbpsi_pmt_es_t ;
struct TYPE_36__ {int i_length; int* p_data; } ;
typedef  TYPE_7__ dvbpsi_descriptor_t ;
struct TYPE_37__ {TYPE_9__* p_sys; } ;
typedef  TYPE_8__ demux_t ;
struct TYPE_38__ {scalar_t__ standard; } ;
typedef  TYPE_9__ demux_sys_t ;
struct TYPE_31__ {int i_subtitling_type; } ;
struct TYPE_30__ {TYPE_4__ fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int GetWBE (int*) ; 
 int /*<<< orphan*/  OpusSetup (TYPE_8__*,int*,int,TYPE_4__*) ; 
 TYPE_7__* PMTEsFindDescriptor (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ PMTEsHasComponentTagBetween (int /*<<< orphan*/  const*,int,int) ; 
 scalar_t__ PMTEsHasRegistration (TYPE_8__*,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  PMTSetupEsDvbSubtitle (TYPE_8__*,TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PMTSetupEsTeletext (TYPE_8__*,TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PROFILE_DTS_HD ; 
 int /*<<< orphan*/  SPU_ES ; 
 int /*<<< orphan*/  SetupTTMLExtendedDescriptor (TYPE_8__*,TYPE_7__*,TYPE_4__*) ; 
 scalar_t__ TS_STANDARD_ARIB ; 
 scalar_t__ UNKNOWN_ES ; 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_302M ; 
 int /*<<< orphan*/  VLC_CODEC_A52 ; 
 int /*<<< orphan*/  VLC_CODEC_ARIB_A ; 
 int /*<<< orphan*/  VLC_CODEC_ARIB_C ; 
 int /*<<< orphan*/  VLC_CODEC_DTS ; 
 int /*<<< orphan*/  VLC_CODEC_EAC3 ; 
 int /*<<< orphan*/  VLC_CODEC_HEVC ; 
 int /*<<< orphan*/  VLC_CODEC_TTML_TS ; 
 int /*<<< orphan*/  VLC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_6__* dvbpsi_DecodeStreamIdentifierDr (TYPE_7__*) ; 
 TYPE_5__* dvbpsi_DecodeSubtitlingDr (TYPE_7__*) ; 
 int /*<<< orphan*/  es_format_Change (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_8__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_8__*,char*,int) ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 void* strndup (char*,int) ; 

__attribute__((used)) static void PMTSetupEs0x06( demux_t *p_demux, ts_stream_t *p_pes,
                            const dvbpsi_pmt_es_t *p_dvbpsies )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    es_format_t *p_fmt = &p_pes->p_es->fmt;
    dvbpsi_descriptor_t *p_subs_dr = PMTEsFindDescriptor( p_dvbpsies, 0x59 );
    dvbpsi_descriptor_t *desc;
    if( PMTEsHasRegistration( p_demux, p_dvbpsies, "EAC3" ) ||
        PMTEsFindDescriptor( p_dvbpsies, 0x7a ) )
    {
        /* DVB with stream_type 0x06 (ETS EN 300 468) */
        es_format_Change( p_fmt, AUDIO_ES, VLC_CODEC_EAC3 );
    }
    else if( PMTEsHasRegistration( p_demux, p_dvbpsies, "AC-3" ) ||
             PMTEsFindDescriptor( p_dvbpsies, 0x6a ) ||
             PMTEsFindDescriptor( p_dvbpsies, 0x81 ) ) /* AC-3 channel (also in EAC3) */
    {
        es_format_Change( p_fmt, AUDIO_ES, VLC_CODEC_A52 );
    }
    else if( PMTEsHasRegistration( p_demux, p_dvbpsies, "DTS1" ) || /* 512 Bpf */
             PMTEsHasRegistration( p_demux, p_dvbpsies, "DTS2" ) || /* 1024 Bpf */
             PMTEsHasRegistration( p_demux, p_dvbpsies, "DTS3" ) || /* 2048 Bpf */
             PMTEsFindDescriptor( p_dvbpsies, 0x73 ) )
    {
        /*registration descriptor(ETSI TS 101 154 Annex F)*/
        es_format_Change( p_fmt, AUDIO_ES, VLC_CODEC_DTS );
    }
    else if( PMTEsHasRegistration( p_demux, p_dvbpsies, "BSSD" ) && !p_subs_dr )
    {
        /* BSSD is AES3 DATA, but could also be subtitles
         * we need to check for secondary descriptor then s*/
        es_format_Change( p_fmt, AUDIO_ES, VLC_CODEC_302M );
        p_fmt->b_packetized = true;
    }
    else if( PMTEsHasRegistration( p_demux, p_dvbpsies, "HEVC" ) )
    {
        es_format_Change( p_fmt, VIDEO_ES, VLC_CODEC_HEVC );
    }
    else if( (desc = PMTEsFindDescriptor( p_dvbpsies, 0x7f )) &&
             desc->i_length >= 2 )
    {
        /* extended_descriptor on PMT (DVB Bluebook A038) */
        switch( desc->p_data[0] )
        {
            case 0x80: /* User Defined */
                 /* non finalized Opus in TS Draft. Can't really tell...
                  * So ffmpeg produced mixes with System-A reg */
                if( PMTEsHasRegistration(p_demux, p_dvbpsies, "Opus") )
                    OpusSetup(p_demux, desc->p_data, desc->i_length, p_fmt);
                break;
            case 0x0E: /* DTS HD */
                es_format_Change( p_fmt, AUDIO_ES, VLC_CODEC_DTS );
                p_fmt->i_profile = PROFILE_DTS_HD;
                break;
            case 0x0F: /* DTS Neural */
                es_format_Change( p_fmt, AUDIO_ES, VLC_CODEC_DTS );
                break;
            case 0x15: /* AC4, unsupported for now */
                es_format_Change( p_fmt, AUDIO_ES, VLC_FOURCC('A', 'C', '-', '4') );
                break;
            case 0x20:
                es_format_Change( p_fmt, SPU_ES, VLC_CODEC_TTML_TS );
                SetupTTMLExtendedDescriptor( p_demux, desc, p_fmt );
                break;
        }
    }
    else if( p_sys->standard == TS_STANDARD_ARIB )
    {
        /* Lookup our data component descriptor first ARIB STD B10 6.4 */
        dvbpsi_descriptor_t *p_dr = PMTEsFindDescriptor( p_dvbpsies, 0xFD );
        /* and check that it maps to something ARIB STD B14 Table 5.1/5.2 */
        if ( p_dr && p_dr->i_length >= 2 )
        {
            /* See STD-B10 Annex J, table J-1 mappings */
            const uint16_t i_data_component_id = GetWBE(p_dr->p_data);
            if( i_data_component_id == 0x0008 &&
                PMTEsHasComponentTagBetween( p_dvbpsies, 0x30, 0x37 ) )
            {
                es_format_Change( p_fmt, SPU_ES, VLC_CODEC_ARIB_A );
                p_fmt->psz_language = strndup ( "jpn", 3 );
                p_fmt->psz_description = strdup( _("ARIB subtitles") );
            }
            else if( i_data_component_id == 0x0012 &&
                     PMTEsHasComponentTagBetween( p_dvbpsies, 0x87, 0x88 ) )
            {
                es_format_Change( p_fmt, SPU_ES, VLC_CODEC_ARIB_C );
                p_fmt->psz_language = strndup ( "jpn", 3 );
                p_fmt->psz_description = strdup( _("ARIB subtitles") );
            }
        }
    }
    else
    {
        /* Subtitle/Teletext/VBI fallbacks */
        dvbpsi_subtitling_dr_t *p_sub;
        if( p_subs_dr && ( p_sub = dvbpsi_DecodeSubtitlingDr( p_subs_dr ) ) )
        {
            for( int i = 0; i < p_sub->i_subtitles_number; i++ )
            {
                if( p_fmt->i_cat != UNKNOWN_ES )
                    break;

                switch( p_sub->p_subtitle[i].i_subtitling_type )
                {
                case 0x01: /* EBU Teletext subtitles */
                case 0x02: /* Associated EBU Teletext */
                case 0x03: /* VBI data */
                    PMTSetupEsTeletext( p_demux, p_pes, p_dvbpsies );
                    break;
                case 0x10: /* DVB Subtitle (normal) with no monitor AR critical */
                case 0x11: /*                 ...   on 4:3 AR monitor */
                case 0x12: /*                 ...   on 16:9 AR monitor */
                case 0x13: /*                 ...   on 2.21:1 AR monitor */
                case 0x14: /*                 ...   for display on a high definition monitor */
                case 0x20: /* DVB Subtitle (impaired) with no monitor AR critical */
                case 0x21: /*                 ...   on 4:3 AR monitor */
                case 0x22: /*                 ...   on 16:9 AR monitor */
                case 0x23: /*                 ...   on 2.21:1 AR monitor */
                case 0x24: /*                 ...   for display on a high definition monitor */
                    PMTSetupEsDvbSubtitle( p_demux, p_pes, p_dvbpsies );
                    break;
                default:
                    msg_Err( p_demux, "Unrecognized DVB subtitle type (0x%x)",
                             p_sub->p_subtitle[i].i_subtitling_type );
                    break;
                }
            }
        }

        if( p_fmt->i_cat == UNKNOWN_ES &&
            ( PMTEsFindDescriptor( p_dvbpsies, 0x45 ) ||  /* VBI Data descriptor */
              PMTEsFindDescriptor( p_dvbpsies, 0x46 ) ||  /* VBI Teletext descriptor */
              PMTEsFindDescriptor( p_dvbpsies, 0x56 ) ) ) /* EBU Teletext descriptor */
        {
            /* Teletext/VBI */
            PMTSetupEsTeletext( p_demux, p_pes, p_dvbpsies );
        }
    }

    /* FIXME is it useful ? */
    if( PMTEsFindDescriptor( p_dvbpsies, 0x52 ) )
    {
        dvbpsi_descriptor_t *p_dr = PMTEsFindDescriptor( p_dvbpsies, 0x52 );
        dvbpsi_stream_identifier_dr_t *p_si = dvbpsi_DecodeStreamIdentifierDr( p_dr );

        msg_Dbg( p_demux, "    * Stream Component Identifier: %d", p_si->i_component_tag );
    }
}