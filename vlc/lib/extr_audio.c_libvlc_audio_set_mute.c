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
 int aout_MuteSet (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  aout_Release (int /*<<< orphan*/ *) ; 

void libvlc_audio_set_mute( libvlc_media_player_t *mp, int mute )
{
    audio_output_t *aout = GetAOut( mp );
    if( aout != NULL )
    {
        mute = aout_MuteSet( aout, mute );
        aout_Release(aout);
    }
}