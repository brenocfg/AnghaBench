#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  joinable_inputs; int /*<<< orphan*/  inputs; int /*<<< orphan*/  stopping_inputs; } ;
struct TYPE_9__ {TYPE_1__ destructor; } ;
typedef  TYPE_4__ vlc_player_t ;
struct vlc_player_input {int started; TYPE_3__* player; int /*<<< orphan*/  node; } ;
struct TYPE_7__ {int /*<<< orphan*/  wait; } ;
struct TYPE_8__ {TYPE_2__ destructor; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_list_HasInput (int /*<<< orphan*/ *,struct vlc_player_input*) ; 
 int /*<<< orphan*/  vlc_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vlc_player_destructor_AddInput(vlc_player_t *player,
                               struct vlc_player_input *input)
{
    if (input->started)
    {
        input->started = false;
        /* Add this input to the stop list: it will be stopped by the
         * destructor thread */
        assert(!vlc_list_HasInput(&player->destructor.stopping_inputs, input));
        assert(!vlc_list_HasInput(&player->destructor.joinable_inputs, input));
        vlc_list_append(&input->node, &player->destructor.inputs);
    }
    else
    {
        /* Add this input to the joinable list: it will be deleted by the
         * destructor thread */
        assert(!vlc_list_HasInput(&player->destructor.inputs, input));
        assert(!vlc_list_HasInput(&player->destructor.joinable_inputs, input));
        vlc_list_append(&input->node, &player->destructor.joinable_inputs);
    }

    vlc_cond_signal(&input->player->destructor.wait);
}