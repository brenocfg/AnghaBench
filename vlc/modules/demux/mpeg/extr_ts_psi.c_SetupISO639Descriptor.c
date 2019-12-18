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
typedef  int uint8_t ;
struct TYPE_8__ {char* psz_language; scalar_t__ i_extra_languages; TYPE_4__* p_extra_languages; scalar_t__ i_priority; void* psz_description; } ;
struct TYPE_10__ {TYPE_1__ fmt; } ;
typedef  TYPE_3__ ts_es_t ;
struct TYPE_11__ {char* psz_language; void* psz_description; } ;
typedef  TYPE_4__ extra_languages_t ;
struct TYPE_12__ {scalar_t__ i_code_count; TYPE_2__* code; } ;
typedef  TYPE_5__ dvbpsi_iso639_dr_t ;
typedef  int /*<<< orphan*/  dvbpsi_descriptor_t ;
typedef  int /*<<< orphan*/  demux_t ;
struct TYPE_9__ {int i_audio_type; int /*<<< orphan*/  iso_639_code; } ;

/* Variables and functions */
 scalar_t__ ES_PRIORITY_SELECTABLE_MIN ; 
 void* GetIso639AudioTypeDesc (int) ; 
 TYPE_5__* dvbpsi_DecodeISO639Dr (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void SetupISO639Descriptor( demux_t *p_demux, ts_es_t *p_es,
                                   dvbpsi_descriptor_t *p_dr )
{
    dvbpsi_iso639_dr_t *p_decoded = dvbpsi_DecodeISO639Dr( p_dr );
    if( !p_decoded )
    {
        msg_Err( p_demux, "      Failed to decode a ISO 639 descriptor" );
        return;
    }

    if( !p_es->fmt.psz_language )
    {
        p_es->fmt.psz_language = malloc( 4 );
        if( p_es->fmt.psz_language )
        {
            memcpy( p_es->fmt.psz_language, p_decoded->code[0].iso_639_code, 3 );
            p_es->fmt.psz_language[3] = 0;
            msg_Dbg( p_demux, "      found language: %s", p_es->fmt.psz_language);
        }
    }

    uint8_t type = p_decoded->code[0].i_audio_type;
    if( !p_es->fmt.psz_description )
        p_es->fmt.psz_description = GetIso639AudioTypeDesc( type );
    if (type == 0x00) /* Undefined */
        p_es->fmt.i_priority = ES_PRIORITY_SELECTABLE_MIN + 1; // prioritize normal audio tracks

    if( p_es->fmt.p_extra_languages )
        return;

    p_es->fmt.i_extra_languages = p_decoded->i_code_count-1;
    if( p_es->fmt.i_extra_languages > 0 )
        p_es->fmt.p_extra_languages =
            malloc( sizeof(*p_es->fmt.p_extra_languages) *
                    p_es->fmt.i_extra_languages );
    if( p_es->fmt.p_extra_languages )
    {
        for( unsigned i = 0; i < p_es->fmt.i_extra_languages; i++ )
        {
            extra_languages_t *p_lang = &p_es->fmt.p_extra_languages[i];
            if( (p_lang->psz_language = malloc(4)) )
            {
                memcpy( p_lang->psz_language, p_decoded->code[i+1].iso_639_code, 3 );
                p_lang->psz_language[3] = '\0';
            }
            p_lang->psz_description = GetIso639AudioTypeDesc( p_decoded->code[i].i_audio_type );
        }
    }
}