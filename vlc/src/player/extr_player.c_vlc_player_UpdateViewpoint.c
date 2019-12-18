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
typedef  int /*<<< orphan*/  vlc_viewpoint_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_input {int /*<<< orphan*/  thread; } ;
struct TYPE_3__ {int /*<<< orphan*/  const viewpoint; } ;
typedef  TYPE_1__ input_control_param_t ;
typedef  enum vlc_player_whence { ____Placeholder_vlc_player_whence } vlc_player_whence ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_CONTROL_SET_VIEWPOINT ; 
 int /*<<< orphan*/  INPUT_CONTROL_UPDATE_VIEWPOINT ; 
 int VLC_PLAYER_WHENCE_ABSOLUTE ; 
 int /*<<< orphan*/  input_ControlPush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 

void
vlc_player_UpdateViewpoint(vlc_player_t *player,
                           const vlc_viewpoint_t *viewpoint,
                           enum vlc_player_whence whence)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);
    if (input)
    {
        input_control_param_t param = { .viewpoint = *viewpoint };
        if (whence == VLC_PLAYER_WHENCE_ABSOLUTE)
            input_ControlPush(input->thread, INPUT_CONTROL_SET_VIEWPOINT,
                              &param);
        else
            input_ControlPush(input->thread, INPUT_CONTROL_UPDATE_VIEWPOINT,
                              &param);
    }
}