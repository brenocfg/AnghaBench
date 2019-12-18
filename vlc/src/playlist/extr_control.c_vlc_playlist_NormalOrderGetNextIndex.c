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
struct TYPE_4__ {size_t size; } ;
struct TYPE_5__ {int repeat; TYPE_1__ items; int /*<<< orphan*/  current; } ;
typedef  TYPE_2__ vlc_playlist_t ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  VLC_PLAYLIST_PLAYBACK_REPEAT_ALL 130 
#define  VLC_PLAYLIST_PLAYBACK_REPEAT_CURRENT 129 
#define  VLC_PLAYLIST_PLAYBACK_REPEAT_NONE 128 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static inline size_t
vlc_playlist_NormalOrderGetNextIndex(vlc_playlist_t *playlist)
{
    switch (playlist->repeat)
    {
        case VLC_PLAYLIST_PLAYBACK_REPEAT_NONE:
        case VLC_PLAYLIST_PLAYBACK_REPEAT_CURRENT:
            if (playlist->current >= (ssize_t) playlist->items.size - 1)
                return -1;
            return playlist->current + 1;
        case VLC_PLAYLIST_PLAYBACK_REPEAT_ALL:
                if (playlist->items.size == 0)
                    return -1;
            return (playlist->current + 1) % playlist->items.size;
        default:
            vlc_assert_unreachable();
    }
}