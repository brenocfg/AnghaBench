#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_6__ {struct vlc_player_input* input; } ;
typedef  TYPE_2__ vlc_player_t ;
struct vlc_player_input {TYPE_1__* abloop_state; TYPE_2__* player; } ;
struct TYPE_5__ {scalar_t__ time; float pos; scalar_t__ set; } ;

/* Variables and functions */
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_player_SetPosition (TYPE_2__*,float) ; 
 int /*<<< orphan*/  vlc_player_SetTime (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void
vlc_player_input_HandleAtoBLoop(struct vlc_player_input *input, vlc_tick_t time,
                                float pos)
{
    vlc_player_t *player = input->player;

    if (player->input != input)
        return;

    assert(input->abloop_state[0].set && input->abloop_state[1].set);

    if (time != VLC_TICK_INVALID
     && input->abloop_state[0].time != VLC_TICK_INVALID
     && input->abloop_state[1].time != VLC_TICK_INVALID)
    {
        if (time >= input->abloop_state[1].time)
            vlc_player_SetTime(player, input->abloop_state[0].time);
    }
    else if (pos >= input->abloop_state[1].pos)
        vlc_player_SetPosition(player, input->abloop_state[0].pos);
}