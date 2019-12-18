#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  libvlc_state_t ;
struct TYPE_3__ {int /*<<< orphan*/ * player; } ;
typedef  TYPE_1__ libvlc_media_player_t ;
typedef  enum vlc_player_state { ____Placeholder_vlc_player_state } vlc_player_state ;
typedef  enum vlc_player_error { ____Placeholder_vlc_player_error } vlc_player_error ;

/* Variables and functions */
 int VLC_PLAYER_ERROR_NONE ; 
#define  VLC_PLAYER_STATE_PAUSED 132 
#define  VLC_PLAYER_STATE_PLAYING 131 
#define  VLC_PLAYER_STATE_STARTED 130 
#define  VLC_PLAYER_STATE_STOPPED 129 
#define  VLC_PLAYER_STATE_STOPPING 128 
 int /*<<< orphan*/  libvlc_Ended ; 
 int /*<<< orphan*/  libvlc_Error ; 
 int /*<<< orphan*/  libvlc_Opening ; 
 int /*<<< orphan*/  libvlc_Paused ; 
 int /*<<< orphan*/  libvlc_Playing ; 
 int /*<<< orphan*/  libvlc_Stopped ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int vlc_player_GetError (int /*<<< orphan*/ *) ; 
 int vlc_player_GetState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 

libvlc_state_t libvlc_media_player_get_state( libvlc_media_player_t *p_mi )
{
    vlc_player_t *player = p_mi->player;
    vlc_player_Lock(player);

    enum vlc_player_error error = vlc_player_GetError(player);
    enum vlc_player_state state = vlc_player_GetState(player);

    vlc_player_Unlock(player);

    if (error != VLC_PLAYER_ERROR_NONE)
        return libvlc_Error;
    switch (state) {
        case VLC_PLAYER_STATE_STOPPED:
            return libvlc_Stopped;
        case VLC_PLAYER_STATE_STOPPING:
            return libvlc_Ended;
        case VLC_PLAYER_STATE_STARTED:
            return libvlc_Opening;
        case VLC_PLAYER_STATE_PLAYING:
            return libvlc_Playing;
        case VLC_PLAYER_STATE_PAUSED:
            return libvlc_Paused;
        default:
            vlc_assert_unreachable();
    }
}