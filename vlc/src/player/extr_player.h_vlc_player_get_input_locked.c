#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct vlc_player_input* input; } ;
typedef  TYPE_1__ vlc_player_t ;
struct vlc_player_input {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_player_assert_locked (TYPE_1__*) ; 

__attribute__((used)) static inline struct vlc_player_input *
vlc_player_get_input_locked(vlc_player_t *player)
{
    vlc_player_assert_locked(player);
    return player->input;
}