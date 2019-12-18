#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_media_list_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_MediaListItemDeleted ; 
 int /*<<< orphan*/  libvlc_event_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlist_em (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlist_item_deleted ; 

__attribute__((used)) static void
install_playlist_observer(libvlc_media_list_player_t * p_mlp)
{
    assert_locked(p_mlp);
    libvlc_event_attach(mlist_em(p_mlp), libvlc_MediaListItemDeleted, mlist_item_deleted, p_mlp);
}