#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {TYPE_4__* p_es; } ;
typedef  TYPE_3__ ts_stream_t ;
struct TYPE_23__ {int i_id; } ;
struct TYPE_24__ {TYPE_1__ dvb; } ;
struct TYPE_27__ {scalar_t__ i_extra; TYPE_2__ subs; int /*<<< orphan*/ * psz_description; int /*<<< orphan*/ * psz_language; scalar_t__ p_extra; } ;
struct TYPE_26__ {TYPE_5__ fmt; int /*<<< orphan*/  p_program; } ;
typedef  TYPE_4__ ts_es_t ;
typedef  TYPE_5__ es_format_t ;
struct TYPE_28__ {int i_subtitles_number; TYPE_7__* p_subtitle; } ;
typedef  TYPE_6__ dvbpsi_subtitling_dr_t ;
struct TYPE_29__ {int i_subtitling_type; int i_composition_page_id; int i_ancillary_page_id; scalar_t__ i_iso6392_language_code; } ;
typedef  TYPE_7__ dvbpsi_subtitle_t ;
typedef  int /*<<< orphan*/  dvbpsi_pmt_es_t ;
struct TYPE_30__ {scalar_t__ i_length; int /*<<< orphan*/  p_data; } ;
typedef  TYPE_8__ dvbpsi_descriptor_t ;
struct TYPE_31__ {TYPE_10__* p_sys; } ;
typedef  TYPE_9__ demux_t ;
struct TYPE_22__ {int /*<<< orphan*/  b_split_es; } ;
typedef  TYPE_10__ demux_sys_t ;

/* Variables and functions */
 TYPE_8__* PMTEsFindDescriptor (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  SPU_ES ; 
 int /*<<< orphan*/  VLC_CODEC_DVBS ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_6__* dvbpsi_DecodeSubtitlingDr (TYPE_8__*) ; 
 int /*<<< orphan*/  es_format_Change (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Copy (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strndup (char*,int) ; 
 TYPE_4__* ts_es_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_stream_Add_es (TYPE_3__*,TYPE_4__*,int) ; 

__attribute__((used)) static void PMTSetupEsDvbSubtitle( demux_t *p_demux, ts_stream_t *p_pes,
                                   const dvbpsi_pmt_es_t *p_dvbpsies )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    es_format_t *p_fmt = &p_pes->p_es->fmt;

    es_format_Change( p_fmt, SPU_ES, VLC_CODEC_DVBS );

    dvbpsi_descriptor_t *p_dr = PMTEsFindDescriptor( p_dvbpsies, 0x59 );
    int i_page = 0;
    dvbpsi_subtitling_dr_t *p_sub = dvbpsi_DecodeSubtitlingDr( p_dr );
    for( int i = 0; p_sub && i < p_sub->i_subtitles_number; i++ )
    {
        const int i_type = p_sub->p_subtitle[i].i_subtitling_type;
        if( ( i_type >= 0x10 && i_type <= 0x14 ) ||
            ( i_type >= 0x20 && i_type <= 0x24 ) )
            i_page++;
    }

    if( !p_sys->b_split_es  || i_page <= 0 )
    {
        p_fmt->subs.dvb.i_id = -1;
        p_fmt->psz_description = strdup( _("DVB subtitles") );

        if( !p_sys->b_split_es && p_dr && p_dr->i_length > 0 )
        {
            /* Descriptor pass-through */
            p_fmt->p_extra = malloc( p_dr->i_length );
            if( p_fmt->p_extra )
            {
                p_fmt->i_extra = p_dr->i_length;
                memcpy( p_fmt->p_extra, p_dr->p_data, p_dr->i_length );
            }
        }
    }
    else
    {
        for( int i = 0; i < p_sub->i_subtitles_number; i++ )
        {
            ts_es_t *p_subs_es;

            /* */
            if( i == 0 )
            {
                p_subs_es = p_pes->p_es;
            }
            else
            {
                p_subs_es = ts_es_New( p_pes->p_es->p_program );
                if( !p_subs_es )
                    break;

                es_format_Copy( &p_subs_es->fmt, p_fmt );
                free( p_subs_es->fmt.psz_language );
                free( p_subs_es->fmt.psz_description );
                p_subs_es->fmt.psz_language = NULL;
                p_subs_es->fmt.psz_description = NULL;

                ts_stream_Add_es( p_pes, p_subs_es, true );
            }

            /* */
            const dvbpsi_subtitle_t *p = &p_sub->p_subtitle[i];
            p_subs_es->fmt.psz_language = strndup( (char *)p->i_iso6392_language_code, 3 );
            switch( p->i_subtitling_type )
            {
            case 0x10: /* unspec. */
            case 0x11: /* 4:3 */
            case 0x12: /* 16:9 */
            case 0x13: /* 2.21:1 */
            case 0x14: /* HD monitor */
                p_subs_es->fmt.psz_description = strdup( _("DVB subtitles") );
                break;
            case 0x20: /* Hearing impaired unspec. */
            case 0x21: /* h.i. 4:3 */
            case 0x22: /* h.i. 16:9 */
            case 0x23: /* h.i. 2.21:1 */
            case 0x24: /* h.i. HD monitor */
                p_subs_es->fmt.psz_description = strdup( _("DVB subtitles: hearing impaired") );
                break;
            default:
                break;
            }

            /* Hack, FIXME */
            p_subs_es->fmt.subs.dvb.i_id = ( p->i_composition_page_id <<  0 ) |
                                      ( p->i_ancillary_page_id   << 16 );
        }
    }
}