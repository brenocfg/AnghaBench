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
 int /*<<< orphan*/  aout_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 
 scalar_t__ var_SetInteger (int /*<<< orphan*/ *,char*,int) ; 

int libvlc_audio_set_channel( libvlc_media_player_t *mp, int channel )
{
    audio_output_t *p_aout = GetAOut( mp );
    int ret = 0;

    if( !p_aout )
        return -1;

    if( var_SetInteger( p_aout, "stereo-mode", channel ) < 0 )
    {
        libvlc_printerr( "Audio channel out of range" );
        ret = -1;
    }
    aout_Release(p_aout);
    return ret;
}