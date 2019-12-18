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
typedef  enum vlc_player_nav { ____Placeholder_vlc_player_nav } vlc_player_nav ;
typedef  enum input_control_e { ____Placeholder_input_control_e } input_control_e ;

/* Variables and functions */
 int INPUT_CONTROL_NAV_ACTIVATE ; 
 int INPUT_CONTROL_NAV_DOWN ; 
 int INPUT_CONTROL_NAV_LEFT ; 
 int INPUT_CONTROL_NAV_MENU ; 
 int INPUT_CONTROL_NAV_POPUP ; 
 int INPUT_CONTROL_NAV_RIGHT ; 
 int INPUT_CONTROL_NAV_UP ; 
#define  VLC_PLAYER_NAV_ACTIVATE 134 
#define  VLC_PLAYER_NAV_DOWN 133 
#define  VLC_PLAYER_NAV_LEFT 132 
#define  VLC_PLAYER_NAV_MENU 131 
#define  VLC_PLAYER_NAV_POPUP 130 
#define  VLC_PLAYER_NAV_RIGHT 129 
#define  VLC_PLAYER_NAV_UP 128 
 int /*<<< orphan*/  input_ControlPushHelper (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 

void
vlc_player_Navigate(vlc_player_t *player, enum vlc_player_nav nav)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);

    if (!input)
        return;

    enum input_control_e control;
    switch (nav)
    {
        case VLC_PLAYER_NAV_ACTIVATE:
            control = INPUT_CONTROL_NAV_ACTIVATE;
            break;
        case VLC_PLAYER_NAV_UP:
            control = INPUT_CONTROL_NAV_UP;
            break;
        case VLC_PLAYER_NAV_DOWN:
            control = INPUT_CONTROL_NAV_DOWN;
            break;
        case VLC_PLAYER_NAV_LEFT:
            control = INPUT_CONTROL_NAV_LEFT;
            break;
        case VLC_PLAYER_NAV_RIGHT:
            control = INPUT_CONTROL_NAV_RIGHT;
            break;
        case VLC_PLAYER_NAV_POPUP:
            control = INPUT_CONTROL_NAV_POPUP;
            break;
        case VLC_PLAYER_NAV_MENU:
            control = INPUT_CONTROL_NAV_MENU;
            break;
        default:
            vlc_assert_unreachable();
    }
    input_ControlPushHelper(input->thread, control, NULL);
}