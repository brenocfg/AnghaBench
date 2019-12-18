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
struct TYPE_3__ {int /*<<< orphan*/  i_int; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_input {int /*<<< orphan*/  thread; int /*<<< orphan*/  started; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_CONTROL_SET_STATE ; 
 int /*<<< orphan*/  OSD_PAUSE_ICON ; 
 int /*<<< orphan*/  OSD_PLAY_ICON ; 
 int /*<<< orphan*/  PAUSE_S ; 
 int /*<<< orphan*/  PLAYING_S ; 
 int VLC_SUCCESS ; 
 int input_ControlPushHelper (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_osd_Icon (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vlc_player_SetPause(vlc_player_t *player, bool pause)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);

    if (!input || !input->started)
        return;

    vlc_value_t val = { .i_int = pause ? PAUSE_S : PLAYING_S };
    int ret = input_ControlPushHelper(input->thread, INPUT_CONTROL_SET_STATE,
                                      &val);

    if (ret == VLC_SUCCESS)
        vlc_player_osd_Icon(player, pause ? OSD_PAUSE_ICON : OSD_PLAY_ICON);
}