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
struct TYPE_4__ {int /*<<< orphan*/  wait; } ;
struct TYPE_5__ {TYPE_1__ destructor; int /*<<< orphan*/  start_delay_cond; int /*<<< orphan*/  aout_listeners_lock; int /*<<< orphan*/  vout_listeners_lock; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ vlc_player_t ;
typedef  enum vlc_player_lock_type { ____Placeholder_vlc_player_lock_type } vlc_player_lock_type ;

/* Variables and functions */
 int VLC_PLAYER_LOCK_REENTRANT ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init_recursive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vlc_player_InitLocks(vlc_player_t *player, enum vlc_player_lock_type lock_type)
{
    if (lock_type == VLC_PLAYER_LOCK_REENTRANT)
        vlc_mutex_init_recursive(&player->lock);
    else
        vlc_mutex_init(&player->lock);

    vlc_mutex_init(&player->vout_listeners_lock);
    vlc_mutex_init(&player->aout_listeners_lock);
    vlc_cond_init(&player->start_delay_cond);
    vlc_cond_init(&player->destructor.wait);
}