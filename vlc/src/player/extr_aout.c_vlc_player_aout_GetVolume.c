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
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_Release (int /*<<< orphan*/ *) ; 
 float aout_VolumeGet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_player_aout_Hold (int /*<<< orphan*/ *) ; 

float
vlc_player_aout_GetVolume(vlc_player_t *player)
{
    audio_output_t *aout = vlc_player_aout_Hold(player);
    if (!aout)
        return -1.f;
    float vol = aout_VolumeGet(aout);
    aout_Release(aout);

    return vol;
}