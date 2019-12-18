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
struct TYPE_6__ {int /*<<< orphan*/  player; int /*<<< orphan*/  player_listener; } ;
typedef  TYPE_1__ vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_PLAYER_LOCK_NORMAL ; 
 int /*<<< orphan*/  player_callbacks ; 
 int /*<<< orphan*/  player_media_provider ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_player_AddListener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_player_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_player_New (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_AssertLocked (TYPE_1__*) ; 

bool
vlc_playlist_PlayerInit(vlc_playlist_t *playlist, vlc_object_t *parent)
{
    playlist->player = vlc_player_New(parent, VLC_PLAYER_LOCK_NORMAL,
                                      &player_media_provider, playlist);
    if (unlikely(!playlist->player))
        return false;

    vlc_player_Lock(playlist->player);
    /* the playlist and the player share the lock */
    vlc_playlist_AssertLocked(playlist);
    playlist->player_listener = vlc_player_AddListener(playlist->player,
                                                       &player_callbacks,
                                                       playlist);
    vlc_player_Unlock(playlist->player);
    if (unlikely(!playlist->player_listener))
    {
        vlc_player_Delete(playlist->player);
        return false;
    }
    return true;
}