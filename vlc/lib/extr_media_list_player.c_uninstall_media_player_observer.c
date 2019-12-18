#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mp_callback_lock; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_MediaPlayerEndReached ; 
 int /*<<< orphan*/  libvlc_event_detach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  media_player_reached_end ; 
 int /*<<< orphan*/  mplayer_em (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uninstall_media_player_observer(libvlc_media_list_player_t * p_mlp)
{
    assert_locked(p_mlp);

    // Allow callbacks to run, because detach() will wait until all callbacks are processed.
    // This is safe because only callbacks are allowed, and there execution will be cancelled.
    vlc_mutex_unlock(&p_mlp->mp_callback_lock);
    libvlc_event_detach(mplayer_em(p_mlp), libvlc_MediaPlayerEndReached, media_player_reached_end, p_mlp);

    // Now, lock back the callback lock. No more callback will be present from this point.
    vlc_mutex_lock(&p_mlp->mp_callback_lock);

    // What is here is safe, because we guarantee that we won't be able to anything concurrently,
    // - except (cancelled) callbacks - thanks to the object_lock.
}