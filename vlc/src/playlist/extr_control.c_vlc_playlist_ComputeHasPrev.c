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
struct TYPE_6__ {int order; } ;
typedef  TYPE_1__ vlc_playlist_t ;

/* Variables and functions */
#define  VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL 129 
#define  VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM 128 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_1__*) ; 
 int vlc_playlist_NormalOrderHasPrev (TYPE_1__*) ; 
 int vlc_playlist_RandomOrderHasPrev (TYPE_1__*) ; 

bool
vlc_playlist_ComputeHasPrev(vlc_playlist_t *playlist)
{
    vlc_playlist_AssertLocked(playlist);
    switch (playlist->order)
    {
        case VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL:
            return vlc_playlist_NormalOrderHasPrev(playlist);
        case VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM:
            return vlc_playlist_RandomOrderHasPrev(playlist);
        default:
            vlc_assert_unreachable();
    }
}