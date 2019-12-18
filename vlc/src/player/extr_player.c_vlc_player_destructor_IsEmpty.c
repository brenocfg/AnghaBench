#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  joinable_inputs; int /*<<< orphan*/  stopping_inputs; int /*<<< orphan*/  inputs; } ;
struct TYPE_5__ {TYPE_1__ destructor; } ;
typedef  TYPE_2__ vlc_player_t ;

/* Variables and functions */
 scalar_t__ vlc_list_is_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool vlc_player_destructor_IsEmpty(vlc_player_t *player)
{
    return vlc_list_is_empty(&player->destructor.inputs)
        && vlc_list_is_empty(&player->destructor.stopping_inputs)
        && vlc_list_is_empty(&player->destructor.joinable_inputs);
}