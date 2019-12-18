#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_input {TYPE_1__* abloop_state; } ;
typedef  enum vlc_player_abloop { ____Placeholder_vlc_player_abloop } vlc_player_abloop ;
struct TYPE_2__ {int set; void* time; float pos; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
#define  VLC_PLAYER_ABLOOP_A 130 
#define  VLC_PLAYER_ABLOOP_B 129 
#define  VLC_PLAYER_ABLOOP_NONE 128 
 int VLC_SUCCESS ; 
 void* VLC_TICK_INVALID ; 
 int /*<<< orphan*/  on_atobloop_changed ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_player_CanSeek (int /*<<< orphan*/ *) ; 
 float vlc_player_GetPosition (int /*<<< orphan*/ *) ; 
 void* vlc_player_GetTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_SendEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void*,float) ; 
 int /*<<< orphan*/  vlc_player_SetPosition (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  vlc_player_SetTime (int /*<<< orphan*/ *,void*) ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 

int
vlc_player_SetAtoBLoop(vlc_player_t *player, enum vlc_player_abloop abloop)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);

    if (!input || !vlc_player_CanSeek(player))
        return VLC_EGENERIC;

    vlc_tick_t time = vlc_player_GetTime(player);
    float pos = vlc_player_GetPosition(player);
    int ret = VLC_SUCCESS;
    switch (abloop)
    {
        case VLC_PLAYER_ABLOOP_A:
            if (input->abloop_state[1].set)
                return VLC_EGENERIC;
            input->abloop_state[0].time = time;
            input->abloop_state[0].pos = pos;
            input->abloop_state[0].set = true;
            break;
        case VLC_PLAYER_ABLOOP_B:
            if (!input->abloop_state[0].set)
                return VLC_EGENERIC;
            input->abloop_state[1].time = time;
            input->abloop_state[1].pos = pos;
            input->abloop_state[1].set = true;
            if (input->abloop_state[0].time != VLC_TICK_INVALID
             && time != VLC_TICK_INVALID)
            {
                if (time > input->abloop_state[0].time)
                {
                    vlc_player_SetTime(player, input->abloop_state[0].time);
                    break;
                }
            }
            else if (pos > input->abloop_state[0].pos)
            {
                vlc_player_SetPosition(player, input->abloop_state[0].pos);
                break;
            }

            /* Error: A time is superior to B time. */
            abloop = VLC_PLAYER_ABLOOP_NONE;
            ret = VLC_EGENERIC;
            /* fall-through */
        case VLC_PLAYER_ABLOOP_NONE:
            input->abloop_state[0].set = input->abloop_state[1].set = false;
            time = VLC_TICK_INVALID;
            pos = 0.f;
            break;
        default:
            vlc_assert_unreachable();
    }
    vlc_player_SendEvent(player, on_atobloop_changed, abloop, time, pos);
    return ret;
}