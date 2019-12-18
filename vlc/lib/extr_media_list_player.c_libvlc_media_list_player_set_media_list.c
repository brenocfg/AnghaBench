#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_media_list_t ;
struct TYPE_7__ {int /*<<< orphan*/ * p_mlist; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  install_playlist_observer (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_media_list_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_list_retain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (TYPE_1__*) ; 
 int /*<<< orphan*/  uninstall_playlist_observer (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock (TYPE_1__*) ; 

void libvlc_media_list_player_set_media_list(libvlc_media_list_player_t * p_mlp, libvlc_media_list_t * p_mlist)
{
    assert (p_mlist);

    lock(p_mlp);
    if (p_mlp->p_mlist)
    {
        uninstall_playlist_observer(p_mlp);
        libvlc_media_list_release(p_mlp->p_mlist);
    }
    libvlc_media_list_retain(p_mlist);
    p_mlp->p_mlist = p_mlist;

    install_playlist_observer(p_mlp);

    unlock(p_mlp);
}