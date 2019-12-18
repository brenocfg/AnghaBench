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
struct TYPE_7__ {int /*<<< orphan*/  aout_listeners_lock; } ;
typedef  TYPE_1__ vlc_player_t ;
struct TYPE_8__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_2__ vlc_player_aout_listener_id ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void
vlc_player_aout_RemoveListener(vlc_player_t *player,
                               vlc_player_aout_listener_id *id)
{
    assert(id);

    vlc_mutex_lock(&player->aout_listeners_lock);
    vlc_list_remove(&id->node);
    vlc_mutex_unlock(&player->aout_listeners_lock);
    free(id);
}