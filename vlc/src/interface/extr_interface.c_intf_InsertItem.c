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
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ input_item_AddOptions (int /*<<< orphan*/ *,unsigned int,char const* const*,unsigned int) ; 
 int /*<<< orphan*/ * input_item_New (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libvlc_GetMainPlaylist (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vlc_playlist_InsertOne (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 

int intf_InsertItem(libvlc_int_t *libvlc, const char *mrl, unsigned optc,
                    const char *const *optv, unsigned flags)
{
    input_item_t *item = input_item_New(mrl, NULL);

    if (unlikely(item == NULL))
        return -1;

    int ret = -1;

    if (input_item_AddOptions(item, optc, optv, flags) == VLC_SUCCESS)
    {
        vlc_playlist_t *playlist = libvlc_GetMainPlaylist(libvlc);
        if (playlist)
        {
            vlc_playlist_Lock(playlist);
            ret = vlc_playlist_InsertOne(playlist, 0, item);
            vlc_playlist_Unlock(playlist);
        }
    }
    input_item_Release(item);
    return ret;
}