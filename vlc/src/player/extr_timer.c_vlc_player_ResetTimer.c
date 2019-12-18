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
struct TYPE_6__ {int /*<<< orphan*/  last_framenum; } ;
struct TYPE_7__ {TYPE_1__ smpte; } ;
struct TYPE_8__ {float input_position; int /*<<< orphan*/  lock; TYPE_2__ smpte_source; void* last_ts; int /*<<< orphan*/  input_normal_time; void* input_length; int /*<<< orphan*/  state; } ;
struct TYPE_9__ {TYPE_3__ timer; } ;
typedef  TYPE_4__ vlc_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  VLC_PLAYER_TIMER_STATE_DISCONTINUITY ; 
 int /*<<< orphan*/  VLC_TICK_0 ; 
 void* VLC_TICK_INVALID ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void
vlc_player_ResetTimer(vlc_player_t *player)
{
    vlc_mutex_lock(&player->timer.lock);

    player->timer.state = VLC_PLAYER_TIMER_STATE_DISCONTINUITY;
    player->timer.input_length = VLC_TICK_INVALID;
    player->timer.input_normal_time = VLC_TICK_0;
    player->timer.last_ts = VLC_TICK_INVALID;
    player->timer.input_position = 0.f;
    player->timer.smpte_source.smpte.last_framenum = ULONG_MAX;

    vlc_mutex_unlock(&player->timer.lock);
}