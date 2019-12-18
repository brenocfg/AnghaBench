#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_GetMainPlaylist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_InheritBool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_playlist_GetCurrentIndex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_GoTo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 

void libvlc_InternalPlay(libvlc_int_t *libvlc)
{
    if (!var_InheritBool(VLC_OBJECT(libvlc), "playlist-autostart"))
        return;
    vlc_playlist_t *playlist = libvlc_GetMainPlaylist(libvlc);
    if (!playlist)
        return;
    vlc_playlist_Lock(playlist);
    if (vlc_playlist_Count(playlist) > 0)
    {
        if (vlc_playlist_GetCurrentIndex(playlist) < 0)
            vlc_playlist_GoTo(playlist, 0);
        vlc_playlist_Start(playlist);
    }
    vlc_playlist_Unlock(playlist);
}