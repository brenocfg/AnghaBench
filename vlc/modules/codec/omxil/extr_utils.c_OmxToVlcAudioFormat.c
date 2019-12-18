#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_2__ {scalar_t__ i_codec; int /*<<< orphan*/  i_fourcc; } ;
typedef  scalar_t__ OMX_AUDIO_CODINGTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 TYPE_1__* audio_format_table ; 
 char* vlc_fourcc_GetDescription (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int OmxToVlcAudioFormat( OMX_AUDIO_CODINGTYPE i_omx_codec,
                       vlc_fourcc_t *pi_fourcc, const char **ppsz_name )
{
    unsigned int i;

    for( i = 0; audio_format_table[i].i_codec != 0; i++ )
        if( audio_format_table[i].i_codec == i_omx_codec ) break;

    if( pi_fourcc ) *pi_fourcc = audio_format_table[i].i_fourcc;
    if( ppsz_name ) *ppsz_name = vlc_fourcc_GetDescription( AUDIO_ES,
                                     audio_format_table[i].i_fourcc );
    return !!audio_format_table[i].i_fourcc;
}