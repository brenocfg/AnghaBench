#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_3__ {int /*<<< orphan*/ * player; } ;
typedef  TYPE_1__ libvlc_media_player_t ;

/* Variables and functions */
 scalar_t__ vlc_player_CanPause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Pause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Resume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 

void libvlc_media_player_set_pause( libvlc_media_player_t *p_mi, int paused )
{
    vlc_player_t *player = p_mi->player;
    vlc_player_Lock(player);

    if (paused)
    {
        if (vlc_player_CanPause(player))
            vlc_player_Pause(player);
        else
            vlc_player_Stop(player);
    }
    else
    {
        vlc_player_Resume(player);
    }

    vlc_player_Unlock(player);
}