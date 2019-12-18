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
typedef  int /*<<< orphan*/  libvlc_media_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_mi; int /*<<< orphan*/  p_mlist; int /*<<< orphan*/  current_playing_item_path; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;
typedef  int /*<<< orphan*/  libvlc_media_list_path_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  install_media_player_observer (TYPE_1__*) ; 
 int /*<<< orphan*/ * libvlc_media_list_item_at_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libvlc_media_player_set_media (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uninstall_media_player_observer (TYPE_1__*) ; 

__attribute__((used)) static void
set_current_playing_item(libvlc_media_list_player_t * p_mlp, libvlc_media_list_path_t path)
{
    assert_locked(p_mlp);

    /* First, save the new path that we are going to play */
    if (p_mlp->current_playing_item_path != path)
    {
        free(p_mlp->current_playing_item_path);
        p_mlp->current_playing_item_path = path;
    }

    if (!path)
        return;

    libvlc_media_t * p_md;
    p_md = libvlc_media_list_item_at_path(p_mlp->p_mlist, path);
    if (!p_md)
        return;

    /* Make sure media_player_reached_end() won't get called */
    uninstall_media_player_observer(p_mlp);

    libvlc_media_player_set_media(p_mlp->p_mi, p_md);

    install_media_player_observer(p_mlp);
    libvlc_media_release(p_md); /* for libvlc_media_list_item_at_index */
}