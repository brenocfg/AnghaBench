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

/* Variables and functions */
 scalar_t__ VLC_PLAYER_STATE_PLAYING ; 
 scalar_t__ vlc_player_GetState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_JumpPos (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ChangePosition(vlc_player_t *player, float increment)
{
    vlc_player_Lock(player);
    if (vlc_player_GetState(player) == VLC_PLAYER_STATE_PLAYING)
        vlc_player_JumpPos(player, increment);
    vlc_player_Unlock(player);
}