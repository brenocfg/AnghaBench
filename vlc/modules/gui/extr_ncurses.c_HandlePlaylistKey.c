#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_t ;
struct vlc_playlist_sort_criterion {int /*<<< orphan*/  order; int /*<<< orphan*/  key; } ;
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct TYPE_8__ {int need_update; int plidx_follow; int /*<<< orphan*/  box_idx; TYPE_1__ pl_item_names; int /*<<< orphan*/  box_lines_total; int /*<<< orphan*/ * playlist; } ;
typedef  TYPE_3__ intf_sys_t ;
typedef  enum vlc_playlist_playback_repeat { ____Placeholder_vlc_playlist_playback_repeat } vlc_playlist_playback_repeat ;
typedef  enum vlc_playlist_playback_order { ____Placeholder_vlc_playlist_playback_order } vlc_playlist_playback_order ;

/* Variables and functions */
#define  KEY_BACKSPACE 133 
#define  KEY_DC 132 
#define  KEY_ENTER 131 
 int /*<<< orphan*/  SearchPlaylist (TYPE_3__*) ; 
 int VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL ; 
 int VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM ; 
#define  VLC_PLAYLIST_PLAYBACK_REPEAT_ALL 130 
#define  VLC_PLAYLIST_PLAYBACK_REPEAT_CURRENT 129 
#define  VLC_PLAYLIST_PLAYBACK_REPEAT_NONE 128 
 int /*<<< orphan*/  VLC_PLAYLIST_SORT_KEY_TITLE ; 
 int /*<<< orphan*/  VLC_PLAYLIST_SORT_ORDER_ASCENDING ; 
 int /*<<< orphan*/  VLC_PLAYLIST_SORT_ORDER_DESCENDING ; 
 int /*<<< orphan*/  vlc_playlist_GetCurrentIndex (int /*<<< orphan*/ *) ; 
 int vlc_playlist_GetPlaybackOrder (int /*<<< orphan*/ *) ; 
 int vlc_playlist_GetPlaybackRepeat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_PlayAt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_RemoveOne (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_SetPlaybackOrder (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_playlist_SetPlaybackRepeat (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_playlist_Sort (int /*<<< orphan*/ *,struct vlc_playlist_sort_criterion*,int) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool HandlePlaylistKey(intf_thread_t *intf, int key)
{
    intf_sys_t *sys = intf->p_sys;
    vlc_playlist_t *playlist = sys->playlist;

    switch(key)
    {
    /* Playlist Settings */
    case 'r':
        vlc_playlist_Lock(playlist);
        enum vlc_playlist_playback_order order_mode =
            vlc_playlist_GetPlaybackOrder(playlist);
        order_mode =
            order_mode == VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL
            ? VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM
            : VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL;
        vlc_playlist_SetPlaybackOrder(playlist, order_mode);
        vlc_playlist_Unlock(playlist);
        return true;
    case 'l':
    case 'R':
        vlc_playlist_Lock(playlist);
        enum vlc_playlist_playback_repeat repeat_mode =
            vlc_playlist_GetPlaybackRepeat(playlist);
        switch (repeat_mode)
        {
            case VLC_PLAYLIST_PLAYBACK_REPEAT_NONE:
                repeat_mode = key == 'l'
                    ? VLC_PLAYLIST_PLAYBACK_REPEAT_ALL
                    : VLC_PLAYLIST_PLAYBACK_REPEAT_CURRENT;
                break;
            case VLC_PLAYLIST_PLAYBACK_REPEAT_ALL:
                repeat_mode = key == 'l'
                    ? VLC_PLAYLIST_PLAYBACK_REPEAT_NONE
                    : VLC_PLAYLIST_PLAYBACK_REPEAT_CURRENT;
                break;
            case VLC_PLAYLIST_PLAYBACK_REPEAT_CURRENT:
                repeat_mode = key == 'l'
                    ? VLC_PLAYLIST_PLAYBACK_REPEAT_ALL
                    : VLC_PLAYLIST_PLAYBACK_REPEAT_NONE;
                break;
        }
        vlc_playlist_SetPlaybackRepeat(playlist, repeat_mode);
        vlc_playlist_Unlock(playlist);
        return true;

    /* Playlist sort */
    case 'o':
    case 'O':
        vlc_playlist_Lock(playlist);
        struct vlc_playlist_sort_criterion criteria =
        {
            .key = VLC_PLAYLIST_SORT_KEY_TITLE,
            .order = key == 'o'
                ? VLC_PLAYLIST_SORT_ORDER_ASCENDING
                : VLC_PLAYLIST_SORT_ORDER_DESCENDING
        };
        vlc_playlist_Sort(playlist, &criteria, 1);
        sys->need_update = true;
        vlc_playlist_Unlock(playlist);
        return true;

    case ';':
        SearchPlaylist(sys);
        return true;

    case 'g':
        vlc_playlist_Lock(playlist);
        sys->box_idx = vlc_playlist_GetCurrentIndex(playlist);
        vlc_playlist_Unlock(playlist);
        sys->plidx_follow = true;
        return true;

    /* Deletion */
    case 'D':
    case KEY_BACKSPACE:
    case 0x7f:
    case KEY_DC:
        if (sys->pl_item_names.size)
        {
            vlc_playlist_Lock(playlist);
            vlc_playlist_RemoveOne(playlist, sys->box_idx);
            if (sys->box_idx >= sys->box_lines_total - 1)
                sys->box_idx = sys->box_lines_total - 2;
            sys->need_update = true;
            vlc_playlist_Unlock(playlist);
        }
        return true;

    case KEY_ENTER:
    case '\r':
    case '\n':
        if (sys->pl_item_names.size)
        {
            vlc_playlist_Lock(playlist);
            vlc_playlist_PlayAt(playlist, sys->box_idx);
            vlc_playlist_Unlock(playlist);
            sys->plidx_follow = true;
        }
        return true;
    }

    return false;
}