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
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_INPUT_OPTION_TRUSTED ; 
 int /*<<< orphan*/  input_item_AddOptions (int /*<<< orphan*/ *,int,char const* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * input_item_New (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_AppendOne (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_to_playlist(vlc_playlist_t *playlist, const char *uri,
                            bool play_now, int options_count,
                            const char *const *options)
{
    input_item_t *media = input_item_New(uri, NULL);
    if (!media)
        return;
    input_item_AddOptions(media, options_count, options,
                          VLC_INPUT_OPTION_TRUSTED);

    vlc_playlist_Lock(playlist);
    vlc_playlist_AppendOne(playlist, media);
    if (play_now)
        vlc_playlist_Start(playlist);
    vlc_playlist_Unlock(playlist);
    input_item_Release(media);
}