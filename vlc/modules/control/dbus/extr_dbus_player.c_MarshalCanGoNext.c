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
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int ssize_t ;
struct TYPE_5__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
typedef  enum vlc_playlist_playback_repeat { ____Placeholder_vlc_playlist_playback_repeat } vlc_playlist_playback_repeat ;
typedef  int dbus_bool_t ;
struct TYPE_4__ {int /*<<< orphan*/ * playlist; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_BOOLEAN ; 
 int VLC_ENOMEM ; 
 int VLC_PLAYLIST_PLAYBACK_REPEAT_NONE ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 size_t vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int vlc_playlist_GetCurrentIndex (int /*<<< orphan*/ *) ; 
 int vlc_playlist_GetPlaybackRepeat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
MarshalCanGoNext( intf_thread_t *p_intf, DBusMessageIter *container )
{
    vlc_playlist_t *playlist = p_intf->p_sys->playlist;
    vlc_playlist_Lock(playlist);
    size_t count = vlc_playlist_Count(playlist);
    ssize_t index = vlc_playlist_GetCurrentIndex(playlist);
    enum vlc_playlist_playback_repeat repeat_mode =
        vlc_playlist_GetPlaybackRepeat(playlist);
    vlc_playlist_Unlock(playlist);

    dbus_bool_t b_can_go_next =
        count != 0 &&
        ((index != -1 && (size_t)index < count - 1) ||
         repeat_mode != VLC_PLAYLIST_PLAYBACK_REPEAT_NONE);

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_BOOLEAN,
                                         &b_can_go_next ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}