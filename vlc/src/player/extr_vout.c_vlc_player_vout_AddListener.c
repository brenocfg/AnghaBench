#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  node; void* cbs_data; struct vlc_player_vout_cbs const* cbs; } ;
typedef  TYPE_1__ vlc_player_vout_listener_id ;
struct TYPE_7__ {int /*<<< orphan*/  vout_listeners_lock; int /*<<< orphan*/  vout_listeners; } ;
typedef  TYPE_2__ vlc_player_t ;
struct vlc_player_vout_cbs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct vlc_player_vout_cbs const*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  vlc_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

vlc_player_vout_listener_id *
vlc_player_vout_AddListener(vlc_player_t *player,
                            const struct vlc_player_vout_cbs *cbs,
                            void *cbs_data)
{
    assert(cbs);

    vlc_player_vout_listener_id *listener = malloc(sizeof(*listener));
    if (!listener)
        return NULL;

    listener->cbs = cbs;
    listener->cbs_data = cbs_data;

    vlc_mutex_lock(&player->vout_listeners_lock);
    vlc_list_append(&listener->node, &player->vout_listeners);
    vlc_mutex_unlock(&player->vout_listeners_lock);

    return listener;
}