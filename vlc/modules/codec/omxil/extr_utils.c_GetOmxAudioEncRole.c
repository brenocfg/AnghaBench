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
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_2__ {scalar_t__ i_codec; scalar_t__ i_fourcc; char const* psz_role; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 TYPE_1__* audio_enc_format_table ; 
 scalar_t__ vlc_fourcc_GetCodec (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static const char *GetOmxAudioEncRole( vlc_fourcc_t i_fourcc )
{
    unsigned int i;

    i_fourcc = vlc_fourcc_GetCodec( AUDIO_ES, i_fourcc );

    for( i = 0; audio_enc_format_table[i].i_codec != 0; i++ )
        if( audio_enc_format_table[i].i_fourcc == i_fourcc ) break;

    return audio_enc_format_table[i].psz_role;
}