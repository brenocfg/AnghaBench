#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__** data; } ;
struct TYPE_12__ {int current; scalar_t__ order; int /*<<< orphan*/  has_next; int /*<<< orphan*/  has_prev; int /*<<< orphan*/  randomizer; TYPE_1__ items; } ;
typedef  TYPE_2__ vlc_playlist_t ;
struct TYPE_13__ {int /*<<< orphan*/ * media; } ;
typedef  TYPE_3__ vlc_playlist_item_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct vlc_playlist_state {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 scalar_t__ VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  randomizer_Select (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasNext (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasPrev (TYPE_2__*) ; 
 int vlc_playlist_IndexOfMedia (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_state_NotifyChanges (TYPE_2__*,struct vlc_playlist_state*) ; 
 int /*<<< orphan*/  vlc_playlist_state_Save (TYPE_2__*,struct vlc_playlist_state*) ; 

__attribute__((used)) static void
player_on_current_media_changed(vlc_player_t *player, input_item_t *new_media,
                                void *userdata)
{
    VLC_UNUSED(player);
    vlc_playlist_t *playlist = userdata;

    /* the playlist and the player share the lock */
    vlc_playlist_AssertLocked(playlist);

    input_item_t *media = playlist->current != -1
                        ? playlist->items.data[playlist->current]->media
                        : NULL;
    if (new_media == media)
        /* nothing to do */
        return;

    ssize_t index;
    if (new_media)
    {
        index = vlc_playlist_IndexOfMedia(playlist, new_media);
        if (index != -1)
        {
            vlc_playlist_item_t *item = playlist->items.data[index];
            if (playlist->order == VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM)
                randomizer_Select(&playlist->randomizer, item);
        }
    }
    else
        index = -1;

    struct vlc_playlist_state state;
    vlc_playlist_state_Save(playlist, &state);

    playlist->current = index;
    playlist->has_prev = vlc_playlist_ComputeHasPrev(playlist);
    playlist->has_next = vlc_playlist_ComputeHasNext(playlist);

    vlc_playlist_state_NotifyChanges(playlist, &state);
}