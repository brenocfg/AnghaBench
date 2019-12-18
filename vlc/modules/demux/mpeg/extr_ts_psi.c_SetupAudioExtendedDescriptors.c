#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_10__ {scalar_t__* psz_language; scalar_t__ i_priority; scalar_t__* psz_description; } ;
struct TYPE_11__ {TYPE_1__ fmt; } ;
typedef  TYPE_2__ ts_es_t ;
typedef  int /*<<< orphan*/  dvbpsi_pmt_es_t ;
struct TYPE_12__ {int i_length; int* p_data; } ;
typedef  TYPE_3__ dvbpsi_descriptor_t ;
struct TYPE_13__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_14__ {scalar_t__ standard; } ;
typedef  TYPE_5__ demux_sys_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
#define  DESC_AUDIO_DESC_VISUALLY_IMPAIRED 131 
#define  DESC_CLEAN_AUDIO_HEARING_IMPAIRED 130 
#define  DESC_MAIN_AUDIO 129 
#define  DESC_SPOKEN_SUBTITLES_VISUAL_IMP 128 
 scalar_t__ ES_PRIORITY_NOT_DEFAULTABLE ; 
 scalar_t__ ES_PRIORITY_SELECTABLE_MIN ; 
 TYPE_3__* PMTEsFindDescriptor (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ TS_STANDARD_AUTO ; 
 scalar_t__ TS_STANDARD_DVB ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int*,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,scalar_t__*) ; 
 scalar_t__* strdup (char const*) ; 

__attribute__((used)) static void SetupAudioExtendedDescriptors( demux_t *p_demux, ts_es_t *p_es,
                                           const dvbpsi_pmt_es_t *p_dvbpsies )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    if( p_sys->standard == TS_STANDARD_AUTO ||
        p_sys->standard == TS_STANDARD_DVB )
    {
        const dvbpsi_descriptor_t *p_dr = PMTEsFindDescriptor( p_dvbpsies, 0x7F );
        if( p_dr && p_dr->i_length > 1 && p_dr->p_data[0] == 0x06 /* Tag extension */ )
        {
            static const char *editorial_classification_coding[] = {
                DESC_MAIN_AUDIO,
                DESC_AUDIO_DESC_VISUALLY_IMPAIRED,
                DESC_CLEAN_AUDIO_HEARING_IMPAIRED,
                DESC_SPOKEN_SUBTITLES_VISUAL_IMP,
            };

            uint8_t i_audio_type = (p_dr->p_data[1] & 0x7F) >> 2;

            if( i_audio_type < ARRAY_SIZE(editorial_classification_coding) )
            {
                free( p_es->fmt.psz_description );
                p_es->fmt.psz_description = strdup(editorial_classification_coding[i_audio_type]);
            }

            if( i_audio_type == 0x00 /* Main Audio */ )
                p_es->fmt.i_priority = ES_PRIORITY_SELECTABLE_MIN + 1;

            if( (p_dr->p_data[1] & 0x80) == 0x00 ) /* Split mixed */
                p_es->fmt.i_priority = ES_PRIORITY_NOT_DEFAULTABLE;

            if( (p_dr->p_data[1] & 0x01) && p_dr->i_length >= 5 )
            {
                free( p_es->fmt.psz_language );
                p_es->fmt.psz_language = malloc( 4 );
                if( p_es->fmt.psz_language )
                {
                    memcpy( p_es->fmt.psz_language, &p_dr->p_data[2], 3 );
                    p_es->fmt.psz_language[3] = 0;
                    msg_Dbg( p_demux, "      found language: %s", p_es->fmt.psz_language );
                }
            }
        }
    }
}