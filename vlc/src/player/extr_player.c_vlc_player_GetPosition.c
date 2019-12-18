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
struct vlc_player_input {int dummy; } ;

/* Variables and functions */
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 
 float vlc_player_input_GetPos (struct vlc_player_input*) ; 

float
vlc_player_GetPosition(vlc_player_t *player)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);

    return input ? vlc_player_input_GetPos(input) : -1.f;
}