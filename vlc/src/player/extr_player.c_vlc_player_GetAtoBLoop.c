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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_player_input {TYPE_1__* abloop_state; } ;
typedef  enum vlc_player_abloop { ____Placeholder_vlc_player_abloop } vlc_player_abloop ;
struct TYPE_2__ {float pos; int /*<<< orphan*/  time; int /*<<< orphan*/  set; } ;

/* Variables and functions */
 int VLC_PLAYER_ABLOOP_A ; 
 int VLC_PLAYER_ABLOOP_B ; 
 int VLC_PLAYER_ABLOOP_NONE ; 
 int /*<<< orphan*/  vlc_player_CanSeek (int /*<<< orphan*/ *) ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 

enum vlc_player_abloop
vlc_player_GetAtoBLoop(vlc_player_t *player, vlc_tick_t *a_time, float *a_pos,
                       vlc_tick_t *b_time, float *b_pos)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);

    if (!input || !vlc_player_CanSeek(player) || !input->abloop_state[0].set)
        return VLC_PLAYER_ABLOOP_NONE;

    if (a_time)
        *a_time = input->abloop_state[0].time;
    if (a_pos)
        *a_pos = input->abloop_state[0].pos;
    if (!input->abloop_state[1].set)
        return VLC_PLAYER_ABLOOP_A;

    if (b_time)
        *b_time = input->abloop_state[1].time;
    if (b_pos)
        *b_pos = input->abloop_state[1].pos;
    return VLC_PLAYER_ABLOOP_B;
}