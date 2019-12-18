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
struct TYPE_8__ {scalar_t__ order; int repeat; int /*<<< orphan*/  player; int /*<<< orphan*/  has_next; int /*<<< orphan*/  has_prev; int /*<<< orphan*/  randomizer; } ;
typedef  TYPE_1__ vlc_playlist_t ;
struct vlc_playlist_state {int dummy; } ;

/* Variables and functions */
 char* N_ (char*) ; 
 scalar_t__ VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM ; 
#define  VLC_PLAYLIST_PLAYBACK_REPEAT_ALL 130 
#define  VLC_PLAYLIST_PLAYBACK_REPEAT_CURRENT 129 
#define  VLC_PLAYLIST_PLAYBACK_REPEAT_NONE 128 
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  on_playback_repeat_changed ; 
 int /*<<< orphan*/  randomizer_SetLoop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_gettext (char const*) ; 
 int /*<<< orphan*/  vlc_player_osd_Message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasNext (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_playlist_ComputeHasPrev (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_playlist_Notify (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_playlist_state_NotifyChanges (TYPE_1__*,struct vlc_playlist_state*) ; 
 int /*<<< orphan*/  vlc_playlist_state_Save (TYPE_1__*,struct vlc_playlist_state*) ; 

__attribute__((used)) static void
vlc_playlist_PlaybackRepeatChanged(vlc_playlist_t *playlist)
{
    if (playlist->order == VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM)
    {
        bool loop = playlist->repeat == VLC_PLAYLIST_PLAYBACK_REPEAT_ALL;
        randomizer_SetLoop(&playlist->randomizer, loop);
    }

    struct vlc_playlist_state state;
    vlc_playlist_state_Save(playlist, &state);

    playlist->has_prev = vlc_playlist_ComputeHasPrev(playlist);
    playlist->has_next = vlc_playlist_ComputeHasNext(playlist);

    vlc_playlist_Notify(playlist, on_playback_repeat_changed, playlist->repeat);
    vlc_playlist_state_NotifyChanges(playlist, &state);

    char const *state_text = NULL;
    switch (playlist->repeat)
    {
        case VLC_PLAYLIST_PLAYBACK_REPEAT_NONE:
            state_text = N_("Off");
            break;
        case VLC_PLAYLIST_PLAYBACK_REPEAT_ALL:
            state_text = N_("All");
            break;
        case VLC_PLAYLIST_PLAYBACK_REPEAT_CURRENT:
            state_text = N_("One");
            break;
    }
    vlc_player_osd_Message(playlist->player,
                           _("Loop: %s"), vlc_gettext(state_text));
    /* vlc_player_osd_Message() does nothing in tests */
    VLC_UNUSED(state_text);
}