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
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int order; scalar_t__ repeat; int /*<<< orphan*/  player; int /*<<< orphan*/  has_next; int /*<<< orphan*/  has_prev; int /*<<< orphan*/  randomizer; TYPE_1__ items; } ;
typedef  TYPE_2__ vlc_playlist_t ;
struct vlc_playlist_state {int dummy; } ;

/* Variables and functions */
 char* N_ (char*) ; 
#define  VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL 129 
#define  VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM 128 
 scalar_t__ VLC_PLAYLIST_PLAYBACK_REPEAT_ALL ; 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  on_playback_order_changed ; 
 int /*<<< orphan*/  randomizer_Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  randomizer_Clear (int /*<<< orphan*/ *) ; 
 scalar_t__ randomizer_Count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  randomizer_SetLoop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_gettext (char const*) ; 
 int /*<<< orphan*/  vlc_player_osd_Message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasNext (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasPrev (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_playlist_Notify (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_playlist_state_NotifyChanges (TYPE_2__*,struct vlc_playlist_state*) ; 
 int /*<<< orphan*/  vlc_playlist_state_Save (TYPE_2__*,struct vlc_playlist_state*) ; 

__attribute__((used)) static void
vlc_playlist_PlaybackOrderChanged(vlc_playlist_t *playlist)
{
    if (playlist->order == VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM)
    {
        /* randomizer is expected to be empty at this point */
        assert(randomizer_Count(&playlist->randomizer) == 0);
        randomizer_Add(&playlist->randomizer, playlist->items.data,
                       playlist->items.size);

        bool loop = playlist->repeat == VLC_PLAYLIST_PLAYBACK_REPEAT_ALL;
        randomizer_SetLoop(&playlist->randomizer, loop);
    }
    else
        /* we don't use the randomizer anymore */
        randomizer_Clear(&playlist->randomizer);

    struct vlc_playlist_state state;
    vlc_playlist_state_Save(playlist, &state);

    playlist->has_prev = vlc_playlist_ComputeHasPrev(playlist);
    playlist->has_next = vlc_playlist_ComputeHasNext(playlist);

    vlc_playlist_Notify(playlist, on_playback_order_changed, playlist->order);
    vlc_playlist_state_NotifyChanges(playlist, &state);

    char const *state_text = NULL;
    switch (playlist->order)
    {
        case VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL:
            state_text = N_("Off");
            break;
        case VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM:
            state_text = N_("On");
            break;
    }
    vlc_player_osd_Message(playlist->player,
                           _("Random: %s"), vlc_gettext(state_text));
    /* vlc_player_osd_Message() does nothing in tests */
    VLC_UNUSED(state_text);
}