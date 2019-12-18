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

/* Variables and functions */
 int asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  module_exists (char const*) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char*) ; 

int libvlc_audio_output_set( libvlc_media_player_t *mp, const char *psz_name )
{
    char *value;

    if( !module_exists( psz_name )
     || asprintf( &value, "%s,none", psz_name ) == -1 )
        return -1;
    var_SetString( mp, "aout", value );
    free( value );

    return 0;
}