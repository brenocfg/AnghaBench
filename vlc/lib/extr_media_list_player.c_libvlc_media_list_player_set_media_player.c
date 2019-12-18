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
typedef  int /*<<< orphan*/  libvlc_media_player_t ;
struct TYPE_7__ {int /*<<< orphan*/ * p_mi; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  install_media_player_observer (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_media_player_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_player_retain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (TYPE_1__*) ; 
 int /*<<< orphan*/  uninstall_media_player_observer (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock (TYPE_1__*) ; 

void libvlc_media_list_player_set_media_player(libvlc_media_list_player_t * p_mlp, libvlc_media_player_t * p_mi)
{
    libvlc_media_player_t *p_oldmi;

    assert(p_mi != NULL);
    libvlc_media_player_retain(p_mi);

    lock(p_mlp);
    uninstall_media_player_observer(p_mlp);
    p_oldmi = p_mlp->p_mi;
    p_mlp->p_mi = p_mi;
    install_media_player_observer(p_mlp);
    unlock(p_mlp);

    libvlc_media_player_release(p_oldmi);
}