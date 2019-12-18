#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  event_manager; int /*<<< orphan*/ * current_playing_item_path; int /*<<< orphan*/  p_mi; } ;
typedef  TYPE_1__ libvlc_media_list_player_t ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ libvlc_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  install_media_player_observer (TYPE_1__*) ; 
 int /*<<< orphan*/  libvlc_MediaListPlayerStopped ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  libvlc_media_player_stop_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uninstall_media_player_observer (TYPE_1__*) ; 

__attribute__((used)) static void stop(libvlc_media_list_player_t * p_mlp)
{
    assert_locked(p_mlp);

    /* We are not interested in getting media stop event now */
    uninstall_media_player_observer(p_mlp);
    libvlc_media_player_stop_async(p_mlp->p_mi);
    install_media_player_observer(p_mlp);

    free(p_mlp->current_playing_item_path);
    p_mlp->current_playing_item_path = NULL;

    /* Send the event */
    libvlc_event_t event;
    event.type = libvlc_MediaListPlayerStopped;
    libvlc_event_send(&p_mlp->event_manager, &event);
}