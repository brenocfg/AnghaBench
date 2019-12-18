#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  wait; } ;
struct TYPE_11__ {int deleting; scalar_t__ renderer; int /*<<< orphan*/  resource; scalar_t__ next_media; scalar_t__ media; TYPE_1__ destructor; int /*<<< orphan*/  lock; int /*<<< orphan*/  aout_listeners; int /*<<< orphan*/  vout_listeners; int /*<<< orphan*/  listeners; scalar_t__ input; } ;
typedef  TYPE_2__ vlc_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_Release (scalar_t__) ; 
 int /*<<< orphan*/  input_resource_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_DelCallback (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_list_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_player_CorkCallback ; 
 int /*<<< orphan*/  vlc_player_DestroyLocks (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_player_DestroyTimer (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_player_aout_DelCallbacks (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_player_destructor_AddInput (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  vlc_renderer_item_release (scalar_t__) ; 

void
vlc_player_Delete(vlc_player_t *player)
{
    vlc_mutex_lock(&player->lock);

    if (player->input)
        vlc_player_destructor_AddInput(player, player->input);

    player->deleting = true;
    vlc_cond_signal(&player->destructor.wait);

    assert(vlc_list_is_empty(&player->listeners));
    assert(vlc_list_is_empty(&player->vout_listeners));
    assert(vlc_list_is_empty(&player->aout_listeners));

    vlc_mutex_unlock(&player->lock);

    vlc_join(player->destructor.thread, NULL);

    if (player->media)
        input_item_Release(player->media);
    if (player->next_media)
        input_item_Release(player->next_media);

    vlc_player_DestroyLocks(player);

    vlc_player_DestroyTimer(player);

    vlc_player_aout_DelCallbacks(player);
    var_DelCallback(player, "corks", vlc_player_CorkCallback, NULL);

    input_resource_Release(player->resource);
    if (player->renderer)
        vlc_renderer_item_release(player->renderer);

    vlc_object_delete(player);
}