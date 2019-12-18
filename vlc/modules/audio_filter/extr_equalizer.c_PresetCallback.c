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
struct TYPE_8__ {char* psz_string; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_9__ {int /*<<< orphan*/  rem; int /*<<< orphan*/  quot; } ;
typedef  TYPE_2__ lldiv_t ;
struct TYPE_10__ {float* f_amp; int /*<<< orphan*/  f_preamp; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_3__ eqz_preset_t ;

/* Variables and functions */
 unsigned int EQZ_BANDS_MAX ; 
 unsigned int NB_PRESETS ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int asprintf (char**,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* eqz_preset_10b ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__ lldiv (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lroundf (float) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetFloat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int PresetCallback( vlc_object_t *p_aout, char const *psz_cmd,
                         vlc_value_t oldval, vlc_value_t newval, void *p_data )
{
    const eqz_preset_t *preset = NULL;
    const char *psz_preset = newval.psz_string;

    for( unsigned i = 0; i < NB_PRESETS; i++ )
        if( !strcasecmp( eqz_preset_10b[i].psz_name, psz_preset ) )
        {
            preset = eqz_preset_10b + i;
            break;
        }

    if( preset == NULL )
    {
        msg_Err( p_aout, "equalizer preset '%s' not found", psz_preset );
        msg_Info( p_aout, "full list:" );
        for( unsigned i = 0; i < NB_PRESETS; i++ )
             msg_Info( p_aout, "  - '%s'", eqz_preset_10b[i].psz_name );
        return VLC_EGENERIC;
    }

    char *bands = NULL;

    for( unsigned i = 0; i < EQZ_BANDS_MAX; i++ )
    {
        char *psz;

        lldiv_t d = lldiv( lroundf(preset->f_amp[i] * 10000000.f), 10000000 );

        if( asprintf( &psz, "%s %lld.%07llu", i ? bands : "",
                      d.quot, d.rem ) == -1 )
            psz = NULL;

        free( bands );
        if( unlikely(psz == NULL) )
            return VLC_ENOMEM;
        bands = psz;
    }

    var_SetFloat( p_aout, "equalizer-preamp", preset->f_preamp );
    var_SetString( p_aout, "equalizer-bands", bands );
    free( bands );
    (void) psz_cmd; (void) oldval; (void) p_data;
    return VLC_SUCCESS;
}