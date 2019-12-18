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
struct TYPE_5__ {int /*<<< orphan*/  stopping_inputs; } ;
struct TYPE_6__ {TYPE_1__ destructor; } ;
typedef  TYPE_2__ vlc_player_t ;
struct vlc_player_input {int /*<<< orphan*/  started; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ vlc_list_HasInput (int /*<<< orphan*/ *,struct vlc_player_input*) ; 
 int /*<<< orphan*/  vlc_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_destructor_AddInput (TYPE_2__*,struct vlc_player_input*) ; 

void
vlc_player_destructor_AddJoinableInput(vlc_player_t *player,
                                       struct vlc_player_input *input)
{
    if (vlc_list_HasInput(&player->destructor.stopping_inputs, input))
        vlc_list_remove(&input->node);

    assert(!input->started);
    vlc_player_destructor_AddInput(player, input);
}