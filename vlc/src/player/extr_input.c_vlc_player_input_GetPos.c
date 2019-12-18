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
struct TYPE_3__ {struct vlc_player_input* input; } ;
typedef  TYPE_1__ vlc_player_t ;
struct vlc_player_input {float position; TYPE_1__* player; } ;

/* Variables and functions */
 scalar_t__ vlc_player_GetTimerPoint (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,float*) ; 
 int /*<<< orphan*/  vlc_tick_now () ; 

float
vlc_player_input_GetPos(struct vlc_player_input *input)
{
    vlc_player_t *player = input->player;
    float pos;

    if (input == player->input
     && vlc_player_GetTimerPoint(player, vlc_tick_now(), NULL, &pos) == 0)
        return pos;
    return input->position;
}