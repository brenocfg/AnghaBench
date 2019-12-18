#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_media_player_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GetAOut (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_VAR_STRING ; 
 int /*<<< orphan*/  aout_DeviceSet (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  aout_Release (int /*<<< orphan*/ *) ; 
 int asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  var_Type (int /*<<< orphan*/ *,char*) ; 

void libvlc_audio_output_device_set( libvlc_media_player_t *mp,
                                     const char *module, const char *devid )
{
    if( devid == NULL )
        return;

    if( module != NULL )
    {
        char *cfg_name;

        if( asprintf( &cfg_name, "%s-audio-device", module ) == -1 )
            return;

        if( !var_Type( mp, cfg_name ) )
            /* Don't recreate the same variable over and over and over... */
            var_Create( mp, cfg_name, VLC_VAR_STRING );
        var_SetString( mp, cfg_name, devid );
        free( cfg_name );
        return;
    }

    audio_output_t *aout = GetAOut( mp );
    if( aout == NULL )
        return;

    aout_DeviceSet( aout, devid );
    aout_Release(aout);
}