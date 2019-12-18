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
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_2__ {size_t size; } ;
struct vlc_player_input {TYPE_1__ program_vector; } ;

/* Variables and functions */
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 

size_t
vlc_player_GetProgramCount(vlc_player_t *player)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);

    return input ? input->program_vector.size : 0;
}