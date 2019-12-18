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
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  CreateDummyMediaArray (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  DestroyMediaArray (int /*<<< orphan*/ **,int) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int vlc_playlist_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  vlc_playlist_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_Get (int /*<<< orphan*/ *,int) ; 
 int vlc_playlist_IndexOf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlc_playlist_IndexOfMedia (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_RemoveOne (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_playlist_item_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_item_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_index_of(void)
{
    vlc_playlist_t *playlist = vlc_playlist_New(NULL);
    assert(playlist);

    input_item_t *media[10];
    CreateDummyMediaArray(media, 10);

    /* initial playlist with 9 items (1 is not added) */
    int ret = vlc_playlist_Append(playlist, media, 9);
    assert(ret == VLC_SUCCESS);

    assert(vlc_playlist_IndexOfMedia(playlist, media[4]) == 4);
    /* only items 0 to 8 were added */
    assert(vlc_playlist_IndexOfMedia(playlist, media[9]) == -1);

    vlc_playlist_item_t *item = vlc_playlist_Get(playlist, 4);
    assert(vlc_playlist_IndexOf(playlist, item) == 4);

    vlc_playlist_item_Hold(item);
    vlc_playlist_RemoveOne(playlist, 4);
    assert(vlc_playlist_IndexOf(playlist, item) == -1);
    vlc_playlist_item_Release(item);

    DestroyMediaArray(media, 10);
    vlc_playlist_Delete(playlist);
}