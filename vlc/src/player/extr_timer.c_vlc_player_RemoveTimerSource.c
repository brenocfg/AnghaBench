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
struct TYPE_6__ {int /*<<< orphan*/  lock; struct vlc_player_timer_source* sources; } ;
struct TYPE_7__ {TYPE_2__ timer; } ;
typedef  TYPE_3__ vlc_player_t ;
typedef  int /*<<< orphan*/  vlc_es_id_t ;
struct TYPE_5__ {scalar_t__ system_date; } ;
struct vlc_player_timer_source {int /*<<< orphan*/ * es; TYPE_1__ point; } ;

/* Variables and functions */
 size_t VLC_PLAYER_TIMER_TYPE_COUNT ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void
vlc_player_RemoveTimerSource(vlc_player_t *player, vlc_es_id_t *es_source)
{
    vlc_mutex_lock(&player->timer.lock);
    for (size_t i = 0; i < VLC_PLAYER_TIMER_TYPE_COUNT; ++i)
    {
        struct vlc_player_timer_source *source = &player->timer.sources[i];
        if (source->es == es_source)
        {
            /* Discontinuity should have been already signaled */
            assert(source->point.system_date == VLC_TICK_INVALID);
            source->es = NULL;
        }
    }
    vlc_mutex_unlock(&player->timer.lock);
}