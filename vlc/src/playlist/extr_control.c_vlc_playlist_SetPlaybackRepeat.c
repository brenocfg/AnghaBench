#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int repeat; } ;
typedef  TYPE_1__ vlc_playlist_t ;
typedef  enum vlc_playlist_playback_repeat { ____Placeholder_vlc_playlist_playback_repeat } vlc_playlist_playback_repeat ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_playlist_PlaybackRepeatChanged (TYPE_1__*) ; 

void
vlc_playlist_SetPlaybackRepeat(vlc_playlist_t *playlist,
                               enum vlc_playlist_playback_repeat repeat)
{
    vlc_playlist_AssertLocked(playlist);

    if (playlist->repeat == repeat)
        return;

    playlist->repeat = repeat;
    vlc_playlist_PlaybackRepeatChanged(playlist);
}