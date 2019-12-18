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
 int /*<<< orphan*/  var_AddCallback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_AoutCallback ; 
 int /*<<< orphan*/ * vlc_player_aout_Hold (int /*<<< orphan*/ *) ; 

void
vlc_player_aout_AddCallbacks(vlc_player_t *player)
{
    audio_output_t *aout = vlc_player_aout_Hold(player);
    if (!aout)
        return;

    var_AddCallback(aout, "volume", vlc_player_AoutCallback, player);
    var_AddCallback(aout, "mute", vlc_player_AoutCallback, player);
    var_AddCallback(aout, "device", vlc_player_AoutCallback, player);

    aout_Release(aout);
}