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
 int /*<<< orphan*/  CreateDummyMediaArray (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  DestroyMediaArray (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  EXPECT_AT (int,int) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int vlc_playlist_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int vlc_playlist_AppendOne (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_New (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_append(void)
{
    vlc_playlist_t *playlist = vlc_playlist_New(NULL);
    assert(playlist);

    input_item_t *media[10];
    CreateDummyMediaArray(media, 10);

    /* append one by one */
    for (int i = 0; i < 5; ++i)
    {
        int ret = vlc_playlist_AppendOne(playlist, media[i]);
        assert(ret == VLC_SUCCESS);
    }

    /* append several at once */
    int ret = vlc_playlist_Append(playlist, &media[5], 5);
    assert(ret == VLC_SUCCESS);

    assert(vlc_playlist_Count(playlist) == 10);
    EXPECT_AT(0, 0);
    EXPECT_AT(1, 1);
    EXPECT_AT(2, 2);
    EXPECT_AT(3, 3);
    EXPECT_AT(4, 4);
    EXPECT_AT(5, 5);
    EXPECT_AT(6, 6);
    EXPECT_AT(7, 7);
    EXPECT_AT(8, 8);
    EXPECT_AT(9, 9);

    DestroyMediaArray(media, 10);
    vlc_playlist_Delete(playlist);
}