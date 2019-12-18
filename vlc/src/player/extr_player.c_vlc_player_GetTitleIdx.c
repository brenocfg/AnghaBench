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
struct vlc_player_title {int dummy; } ;
struct vlc_player_input {TYPE_1__* titles; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {size_t count; struct vlc_player_title const* array; } ;

/* Variables and functions */
 struct vlc_player_input* vlc_player_get_input_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
vlc_player_GetTitleIdx(vlc_player_t *player,
                       const struct vlc_player_title *title)
{
    struct vlc_player_input *input = vlc_player_get_input_locked(player);
    if (input && input->titles)
        for (size_t i = 0; i < input->titles->count; ++i)
            if (&input->titles->array[i] == title)
                return i;
    return -1;
}