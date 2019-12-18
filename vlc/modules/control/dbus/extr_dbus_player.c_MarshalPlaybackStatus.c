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
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_5__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ intf_thread_t ;
typedef  enum vlc_player_state { ____Placeholder_vlc_player_state } vlc_player_state ;
struct TYPE_4__ {int /*<<< orphan*/  playlist; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 char* PLAYBACK_STATUS_PAUSED ; 
 char* PLAYBACK_STATUS_PLAYING ; 
 char* PLAYBACK_STATUS_STOPPED ; 
 int VLC_ENOMEM ; 
#define  VLC_PLAYER_STATE_PAUSED 130 
#define  VLC_PLAYER_STATE_PLAYING 129 
#define  VLC_PLAYER_STATE_STARTED 128 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  dbus_message_iter_append_basic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**) ; 
 int vlc_player_GetState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_GetPlayer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
MarshalPlaybackStatus( intf_thread_t *p_intf, DBusMessageIter *container )
{
    vlc_player_t *player = vlc_playlist_GetPlayer(p_intf->p_sys->playlist);
    vlc_player_Lock(player);
    enum vlc_player_state state = vlc_player_GetState(player);
    vlc_player_Unlock(player);

    const char *psz_playback_status;
    switch (state)
    {
        case VLC_PLAYER_STATE_STARTED:
        case VLC_PLAYER_STATE_PLAYING:
            psz_playback_status = PLAYBACK_STATUS_PLAYING;
            break;
        case VLC_PLAYER_STATE_PAUSED:
            psz_playback_status = PLAYBACK_STATUS_PAUSED;
            break;
        default:
            psz_playback_status = PLAYBACK_STATUS_STOPPED;
    }

    if( !dbus_message_iter_append_basic( container, DBUS_TYPE_STRING,
                                         &psz_playback_status ) )
        return VLC_ENOMEM;

    return VLC_SUCCESS;
}