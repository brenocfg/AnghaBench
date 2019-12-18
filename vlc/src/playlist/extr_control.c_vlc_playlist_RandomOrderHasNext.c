#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; } ;
struct TYPE_5__ {scalar_t__ repeat; int /*<<< orphan*/  randomizer; TYPE_1__ items; } ;
typedef  TYPE_2__ vlc_playlist_t ;

/* Variables and functions */
 scalar_t__ VLC_PLAYLIST_PLAYBACK_REPEAT_ALL ; 
 int randomizer_HasNext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
vlc_playlist_RandomOrderHasNext(vlc_playlist_t *playlist)
{
    if (playlist->repeat == VLC_PLAYLIST_PLAYBACK_REPEAT_ALL)
        return playlist->items.size > 0;
    return randomizer_HasNext(&playlist->randomizer);
}