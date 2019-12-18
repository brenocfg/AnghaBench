#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_listener_id ;
typedef  int /*<<< orphan*/  vlc_playlist_item_t ;
struct vlc_playlist_callbacks {int /*<<< orphan*/  on_items_removed; } ;
struct TYPE_6__ {int size; TYPE_2__* data; } ;
struct callback_ctx {TYPE_3__ vec_items_removed; } ;
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_4__ {int playlist_size; } ;
struct TYPE_5__ {int index; int count; TYPE_1__ state; } ;

/* Variables and functions */
 struct callback_ctx CALLBACK_CTX_INITIALIZER ; 
 int /*<<< orphan*/  CreateDummyMediaArray (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  DestroyMediaArray (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  EXPECT_AT (int,int) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  callback_ctx_destroy (struct callback_ctx*) ; 
 int /*<<< orphan*/  callback_on_items_removed ; 
 int /*<<< orphan*/ * vlc_playlist_AddListener (int /*<<< orphan*/ *,struct vlc_playlist_callbacks*,struct callback_ctx*,int) ; 
 int vlc_playlist_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_Get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vlc_playlist_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_RemoveListener (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlc_playlist_RequestRemove (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int) ; 
 int /*<<< orphan*/ * vlc_playlist_item_New (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_item_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_request_remove_adapt(void)
{
    vlc_playlist_t *playlist = vlc_playlist_New(NULL);
    assert(playlist);

    input_item_t *media[11];
    CreateDummyMediaArray(media, 11);

    /* initial playlist with 10 items */
    int ret = vlc_playlist_Append(playlist, media, 10);
    assert(ret == VLC_SUCCESS);

    struct vlc_playlist_callbacks cbs = {
        .on_items_removed = callback_on_items_removed,
    };

    struct callback_ctx ctx = CALLBACK_CTX_INITIALIZER;
    vlc_playlist_listener_id *listener =
            vlc_playlist_AddListener(playlist, &cbs, &ctx, false);
    assert(listener);

    vlc_playlist_item_t *dummy = vlc_playlist_item_New(media[10], 0);
    assert(dummy);

    /* remove items in a wrong order at wrong position, as if the playlist had
     * been sorted/shuffled before the request were applied */
    vlc_playlist_item_t *items_to_remove[] = {
        vlc_playlist_Get(playlist, 3),
        vlc_playlist_Get(playlist, 2),
        vlc_playlist_Get(playlist, 6),
        vlc_playlist_Get(playlist, 9),
        vlc_playlist_Get(playlist, 1),
        dummy, /* inexistant */
        vlc_playlist_Get(playlist, 8),
    };

    ret = vlc_playlist_RequestRemove(playlist, items_to_remove, 7, 3);
    assert(ret == VLC_SUCCESS);

    vlc_playlist_item_Release(dummy);

    assert(vlc_playlist_Count(playlist) == 4);

    EXPECT_AT(0, 0);
    EXPECT_AT(1, 4);
    EXPECT_AT(2, 5);
    EXPECT_AT(3, 7);

    /* it should notify 3 different slices removed, in descending order for
     * optimization: {8,9}, {6}, {1,2,3}. */

    assert(ctx.vec_items_removed.size == 3);

    assert(ctx.vec_items_removed.data[0].index == 8);
    assert(ctx.vec_items_removed.data[0].count == 2);
    assert(ctx.vec_items_removed.data[0].state.playlist_size == 8);

    assert(ctx.vec_items_removed.data[1].index == 6);
    assert(ctx.vec_items_removed.data[1].count == 1);
    assert(ctx.vec_items_removed.data[1].state.playlist_size == 7);

    assert(ctx.vec_items_removed.data[2].index == 1);
    assert(ctx.vec_items_removed.data[2].count == 3);
    assert(ctx.vec_items_removed.data[2].state.playlist_size == 4);

    callback_ctx_destroy(&ctx);
    vlc_playlist_RemoveListener(playlist, listener);
    DestroyMediaArray(media, 11);
    vlc_playlist_Delete(playlist);
}