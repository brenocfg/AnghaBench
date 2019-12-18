#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_1__ timer; int /*<<< orphan*/  aout_listeners_lock; int /*<<< orphan*/  vout_listeners_lock; } ;
typedef  TYPE_2__ vlc_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_marked (int /*<<< orphan*/ *) ; 

void
vlc_player_Lock(vlc_player_t *player)
{
    /* Vout and aout locks should not be held, cf. vlc_player_vout_cbs and
     * vlc_player_aout_cbs documentation */
    assert(!vlc_mutex_marked(&player->vout_listeners_lock));
    assert(!vlc_mutex_marked(&player->aout_listeners_lock));
    /* The timer lock should not be held (possible lock-order-inversion), cf.
     * vlc_player_timer_cbs.on_update documentation */
    assert(!vlc_mutex_marked(&player->timer.lock));

    vlc_mutex_lock(&player->lock);
}