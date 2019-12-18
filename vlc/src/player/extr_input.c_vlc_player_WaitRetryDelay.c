#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vlc_tick_t ;
struct TYPE_3__ {unsigned int error_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  start_delay_cond; } ;
typedef  TYPE_1__ vlc_player_t ;

/* Variables and functions */
 int RETRY_TIMEOUT_BASE ; 
 int RETRY_TIMEOUT_MAX ; 
 scalar_t__ vlc_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static bool
vlc_player_WaitRetryDelay(vlc_player_t *player)
{
#define RETRY_TIMEOUT_BASE VLC_TICK_FROM_MS(100)
#define RETRY_TIMEOUT_MAX VLC_TICK_FROM_MS(3200)
    if (player->error_count)
    {
        /* Delay the next opening in case of error to avoid busy loops */
        vlc_tick_t delay = RETRY_TIMEOUT_BASE;
        for (unsigned i = 1; i < player->error_count
          && delay < RETRY_TIMEOUT_MAX; ++i)
            delay *= 2; /* Wait 100, 200, 400, 800, 1600 and finally 3200ms */
        delay += vlc_tick_now();

        while (player->error_count > 0
            && vlc_cond_timedwait(&player->start_delay_cond, &player->lock,
                                  delay) == 0);
        if (player->error_count == 0)
            return false; /* canceled */
    }
    return true;
}