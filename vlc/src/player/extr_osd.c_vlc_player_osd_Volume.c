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
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_MUTE_ICON ; 
 int /*<<< orphan*/  OSD_VERT_SLIDER ; 
 int /*<<< orphan*/  _ (char*) ; 
 int lroundf (float) ; 
 float vlc_player_aout_GetVolume (int /*<<< orphan*/ *) ; 
 int vlc_player_aout_IsMuted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** vlc_player_osd_HoldAll (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  vlc_player_osd_ReleaseAll (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t) ; 
 scalar_t__ vlc_player_vout_IsFullscreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vouts_osd_Icon (int /*<<< orphan*/ **,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vouts_osd_Message (int /*<<< orphan*/ **,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vouts_osd_Slider (int /*<<< orphan*/ **,size_t,int,int /*<<< orphan*/ ) ; 

void
vlc_player_osd_Volume(vlc_player_t *player, bool mute_action)
{
    size_t count;
    vout_thread_t **vouts = vlc_player_osd_HoldAll(player, &count);

    bool mute = vlc_player_aout_IsMuted(player);
    int volume = lroundf(vlc_player_aout_GetVolume(player) * 100.f);
    if (mute_action && mute)
        vouts_osd_Icon(vouts, count, OSD_MUTE_ICON);
    else
    {
        if (vlc_player_vout_IsFullscreen(player))
            vouts_osd_Slider(vouts, count, volume, OSD_VERT_SLIDER);
        vouts_osd_Message(vouts, count, _("Volume: %ld%%"), volume);
    }

    vlc_player_osd_ReleaseAll(player, vouts, count);
}