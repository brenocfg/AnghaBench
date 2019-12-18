#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_2__ vlc_player_timer_id ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {TYPE_1__ timer; } ;
typedef  TYPE_3__ vlc_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void
vlc_player_RemoveTimer(vlc_player_t *player, vlc_player_timer_id *timer)
{
    assert(timer);

    vlc_mutex_lock(&player->timer.lock);
    vlc_list_remove(&timer->node);
    vlc_mutex_unlock(&player->timer.lock);

    free(timer);
}