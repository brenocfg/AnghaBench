#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  listeners; } ;
typedef  TYPE_1__ vlc_playlist_t ;
struct TYPE_10__ {int /*<<< orphan*/  node; void* userdata; struct vlc_playlist_callbacks const* cbs; } ;
typedef  TYPE_2__ vlc_playlist_listener_id ;
struct vlc_playlist_callbacks {int dummy; } ;

/* Variables and functions */
 TYPE_2__* malloc (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_playlist_NotifyCurrentState (TYPE_1__*,TYPE_2__*) ; 

vlc_playlist_listener_id *
vlc_playlist_AddListener(vlc_playlist_t *playlist,
                         const struct vlc_playlist_callbacks *cbs,
                         void *userdata, bool notify_current_state)
{
    vlc_playlist_AssertLocked(playlist);

    vlc_playlist_listener_id *listener = malloc(sizeof(*listener));
    if (unlikely(!listener))
        return NULL;

    listener->cbs = cbs;
    listener->userdata = userdata;
    vlc_list_append(&listener->node, &playlist->listeners);

    if (notify_current_state)
        vlc_playlist_NotifyCurrentState(playlist, listener);

    return listener;
}