#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int order; } ;
typedef  TYPE_1__ vlc_playlist_t ;
typedef  enum vlc_playlist_playback_order { ____Placeholder_vlc_playlist_playback_order } vlc_playlist_playback_order ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_1__*) ; 

enum vlc_playlist_playback_order
vlc_playlist_GetPlaybackOrder(vlc_playlist_t *playlist)
{
    vlc_playlist_AssertLocked(playlist);
    return playlist->order;
}