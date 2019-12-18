#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ i_refcount; struct TYPE_8__* current_playing_item_path; int /*<<< orphan*/  object_lock; int /*<<< orphan*/  mp_callback_lock; int /*<<< orphan*/  seek_pending; int /*<<< orphan*/  event_manager; scalar_t__ p_mlist; int /*<<< orphan*/  p_mi; int /*<<< orphan*/  thread; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_event_manager_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_release (scalar_t__) ; 
 int /*<<< orphan*/  libvlc_media_player_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock (TYPE_1__*) ; 
 int /*<<< orphan*/  uninstall_media_player_observer (TYPE_1__*) ; 
 int /*<<< orphan*/  uninstall_playlist_observer (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

void libvlc_media_list_player_release(libvlc_media_list_player_t * p_mlp)
{
    if (!p_mlp)
        return;

    lock(p_mlp);
    p_mlp->i_refcount--;
    if (p_mlp->i_refcount > 0)
    {
        unlock(p_mlp);
        return;
    }
    assert(p_mlp->i_refcount == 0);
    unlock(p_mlp);

    vlc_cancel(p_mlp->thread);
    vlc_join(p_mlp->thread, NULL);

    lock(p_mlp);
    /* Keep the lock(), because the uninstall functions
     * check for it. That's convenient. */
    uninstall_media_player_observer(p_mlp);
    libvlc_media_player_release(p_mlp->p_mi);

    if (p_mlp->p_mlist)
    {
        uninstall_playlist_observer(p_mlp);
        libvlc_media_list_release(p_mlp->p_mlist);
    }

    unlock(p_mlp);

    libvlc_event_manager_destroy(&p_mlp->event_manager);
    vlc_cond_destroy(&p_mlp->seek_pending);
    vlc_mutex_destroy(&p_mlp->mp_callback_lock);
    vlc_mutex_destroy(&p_mlp->object_lock);

    free(p_mlp->current_playing_item_path);
    free(p_mlp);
}