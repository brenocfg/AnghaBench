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
typedef  int /*<<< orphan*/  vlc_playlist_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * main_playlist; } ;
typedef  TYPE_1__ libvlc_priv_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  PlaylistConfigureFromVariables (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 TYPE_1__* libvlc_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_New (int /*<<< orphan*/ ) ; 

__attribute__((used)) static vlc_playlist_t *
libvlc_GetMainPlaylist(libvlc_int_t *libvlc)
{
    libvlc_priv_t *priv = libvlc_priv(libvlc);

    vlc_mutex_lock(&priv->lock);
    vlc_playlist_t *playlist = priv->main_playlist;
    if (priv->main_playlist == NULL)
    {
        playlist = priv->main_playlist = vlc_playlist_New(VLC_OBJECT(libvlc));
        if (playlist)
            PlaylistConfigureFromVariables(playlist, VLC_OBJECT(libvlc));
    }
    vlc_mutex_unlock(&priv->lock);

    return playlist;
}