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
 int aout_VolumeSet (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  isgreaterequal (float,float) ; 
 int /*<<< orphan*/  libvlc_printerr (char*) ; 

int libvlc_audio_set_volume( libvlc_media_player_t *mp, int volume )
{
    float vol = volume / 100.f;
    if (!isgreaterequal(vol, 0.f))
    {
        libvlc_printerr( "Volume out of range" );
        return -1;
    }

    int ret = -1;
    audio_output_t *aout = GetAOut( mp );
    if( aout != NULL )
    {
        ret = aout_VolumeSet( aout, vol );
        aout_Release(aout);
    }
    return ret;
}