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
struct vlc_player_input {TYPE_1__* abloop_state; } ;
struct TYPE_2__ {scalar_t__ set; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_player_input_GetPos (struct vlc_player_input*) ; 
 int /*<<< orphan*/  vlc_player_input_GetTime (struct vlc_player_input*) ; 
 int /*<<< orphan*/  vlc_player_input_HandleAtoBLoop (struct vlc_player_input*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vlc_player_input_UpdateTime(struct vlc_player_input *input)
{
    if (input->abloop_state[0].set && input->abloop_state[1].set)
        vlc_player_input_HandleAtoBLoop(input, vlc_player_input_GetTime(input),
                                        vlc_player_input_GetPos(input));
}