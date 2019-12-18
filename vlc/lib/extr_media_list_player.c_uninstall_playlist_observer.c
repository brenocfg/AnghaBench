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
struct TYPE_6__ {int /*<<< orphan*/  p_mlist; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_MediaListItemDeleted ; 
 int /*<<< orphan*/  libvlc_event_detach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mlist_em (TYPE_1__*) ; 
 int /*<<< orphan*/  mlist_item_deleted ; 

__attribute__((used)) static void
uninstall_playlist_observer(libvlc_media_list_player_t * p_mlp)
{
    assert_locked(p_mlp);
    if (!p_mlp->p_mlist) return;
    libvlc_event_detach(mlist_em(p_mlp), libvlc_MediaListItemDeleted, mlist_item_deleted, p_mlp);
}