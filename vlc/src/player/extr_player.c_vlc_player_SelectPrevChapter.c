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
struct vlc_player_input {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_CONTROL_SET_SEEKPOINT_PREV ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int input_ControlPush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_osd_Message (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
vlc_player_SelectPrevChapter(vlc_player_t *player)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);
    if (!input)
        return;
    int ret = input_ControlPush(input->thread, INPUT_CONTROL_SET_SEEKPOINT_PREV,
                                NULL);
    if (ret == VLC_SUCCESS)
        vlc_player_osd_Message(player, _("Previous chapter"));
}