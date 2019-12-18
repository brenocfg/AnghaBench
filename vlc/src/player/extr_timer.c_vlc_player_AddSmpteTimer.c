#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vlc_player_timer_id {int /*<<< orphan*/  node; void* data; struct vlc_player_timer_smpte_cbs const* smpte_cbs; void* last_update_date; void* period; } ;
typedef  struct vlc_player_timer_id vlc_player_timer_id ;
struct TYPE_5__ {int /*<<< orphan*/  listeners; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_1__ smpte_source; } ;
struct TYPE_7__ {TYPE_2__ timer; } ;
typedef  TYPE_3__ vlc_player_t ;
struct vlc_player_timer_smpte_cbs {scalar_t__ on_update; } ;

/* Variables and functions */
 void* VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 struct vlc_player_timer_id* malloc (int) ; 
 int /*<<< orphan*/  vlc_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

vlc_player_timer_id *
vlc_player_AddSmpteTimer(vlc_player_t *player,
                         const struct vlc_player_timer_smpte_cbs *cbs,
                         void *data)
{
    assert(cbs && cbs->on_update);

    struct vlc_player_timer_id *timer = malloc(sizeof(*timer));
    if (!timer)
        return NULL;
    timer->period = VLC_TICK_INVALID;
    timer->last_update_date = VLC_TICK_INVALID;
    timer->smpte_cbs = cbs;
    timer->data = data;

    vlc_mutex_lock(&player->timer.lock);
    vlc_list_append(&timer->node, &player->timer.smpte_source.listeners);
    vlc_mutex_unlock(&player->timer.lock);

    return timer;
}