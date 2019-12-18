#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  player; } ;
typedef  TYPE_1__ libvlc_media_player_t ;
struct TYPE_11__ {double* f_amp; int /*<<< orphan*/  f_preamp; } ;
typedef  TYPE_2__ libvlc_equalizer_t ;
typedef  int /*<<< orphan*/  bands ;
typedef  TYPE_1__ audio_output_t ;

/* Variables and functions */
 unsigned int EQZ_BANDS_MAX ; 
 unsigned int EQZ_BAND_VALUE_SIZE ; 
 int /*<<< orphan*/  aout_Release (TYPE_1__*) ; 
 scalar_t__ snprintf (char*,int,char*,double) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  var_SetFloat (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetString (TYPE_1__*,char*,char*) ; 
 TYPE_1__* vlc_player_aout_Hold (int /*<<< orphan*/ ) ; 

int libvlc_media_player_set_equalizer( libvlc_media_player_t *p_mi, libvlc_equalizer_t *p_equalizer )
{
    char bands[EQZ_BANDS_MAX * EQZ_BAND_VALUE_SIZE + 1];

    if( p_equalizer != NULL )
    {
        for( unsigned i = 0, c = 0; i < EQZ_BANDS_MAX; i++ )
        {
            c += snprintf( bands + c, sizeof(bands) - c, " %.07f",
                          p_equalizer->f_amp[i] );
            if( unlikely(c >= sizeof(bands)) )
                return -1;
        }

        var_SetFloat( p_mi, "equalizer-preamp", p_equalizer->f_preamp );
        var_SetString( p_mi, "equalizer-bands", bands );
    }
    var_SetString( p_mi, "audio-filter", p_equalizer ? "equalizer" : "" );

    audio_output_t *p_aout = vlc_player_aout_Hold( p_mi->player );
    if( p_aout != NULL )
    {
        if( p_equalizer != NULL )
        {
            var_SetFloat( p_aout, "equalizer-preamp", p_equalizer->f_preamp );
            var_SetString( p_aout, "equalizer-bands", bands );
        }

        var_SetString( p_aout, "audio-filter", p_equalizer ? "equalizer" : "" );
        aout_Release(p_aout);
    }

    return 0;
}