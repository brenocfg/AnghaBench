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
struct vlc_player_input {scalar_t__ teletext_transparent; } ;

/* Variables and functions */
 scalar_t__ vlc_player_IsTeletextEnabled (int /*<<< orphan*/ *) ; 
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 

bool
vlc_player_IsTeletextTransparent(vlc_player_t *player)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);
    return vlc_player_IsTeletextEnabled(player) && input->teletext_transparent;
}