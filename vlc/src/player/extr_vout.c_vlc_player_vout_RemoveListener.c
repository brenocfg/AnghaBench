#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ vlc_player_vout_listener_id ;
struct TYPE_8__ {int /*<<< orphan*/  vout_listeners_lock; } ;
typedef  TYPE_2__ vlc_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void
vlc_player_vout_RemoveListener(vlc_player_t *player,
                               vlc_player_vout_listener_id *id)
{
    assert(id);

    vlc_mutex_lock(&player->vout_listeners_lock);
    vlc_list_remove(&id->node);
    vlc_mutex_unlock(&player->vout_listeners_lock);
    free(id);
}