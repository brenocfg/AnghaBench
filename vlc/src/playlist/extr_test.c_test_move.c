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
 int /*<<< orphan*/  vlc_playlist_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Move (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/ * vlc_playlist_New (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_move(void)
{
    vlc_playlist_t *playlist = vlc_playlist_New(NULL);
    assert(playlist);

    input_item_t *media[10];
    CreateDummyMediaArray(media, 10);

    /* initial playlist with 10 items */
    int ret = vlc_playlist_Append(playlist, media, 10);
    assert(ret == VLC_SUCCESS);

    /* move slice {3, 4, 5, 6} so that its new position is 5 */
    vlc_playlist_Move(playlist, 3, 4, 5);

    EXPECT_AT(0, 0);
    EXPECT_AT(1, 1);
    EXPECT_AT(2, 2);
    EXPECT_AT(3, 7);
    EXPECT_AT(4, 8);
    EXPECT_AT(5, 3);
    EXPECT_AT(6, 4);
    EXPECT_AT(7, 5);
    EXPECT_AT(8, 6);
    EXPECT_AT(9, 9);

    /* move it back to its original position */
    vlc_playlist_Move(playlist, 5, 4, 3);

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