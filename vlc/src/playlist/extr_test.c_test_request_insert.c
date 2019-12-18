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
struct vlc_playlist_callbacks {int /*<<< orphan*/  on_items_added; } ;
struct TYPE_6__ {int size; TYPE_2__* data; } ;
struct callback_ctx {TYPE_3__ vec_items_added; } ;
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
 int /*<<< orphan*/  callback_on_items_added ; 
 int /*<<< orphan*/ * vlc_playlist_AddListener (int /*<<< orphan*/ *,struct vlc_playlist_callbacks*,struct callback_ctx*,int) ; 
 int vlc_playlist_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int vlc_playlist_Count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_RemoveListener (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlc_playlist_RequestInsert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static void
test_request_insert(void)
{
    vlc_playlist_t *playlist = vlc_playlist_New(NULL);
    assert(playlist);

    input_item_t *media[5];
    CreateDummyMediaArray(media, 5);

    /* initial playlist with 3 items */
    int ret = vlc_playlist_Append(playlist, media, 3);
    assert(ret == VLC_SUCCESS);

    struct vlc_playlist_callbacks cbs = {
        .on_items_added = callback_on_items_added,
    };

    struct callback_ctx ctx = CALLBACK_CTX_INITIALIZER;
    vlc_playlist_listener_id *listener =
            vlc_playlist_AddListener(playlist, &cbs, &ctx, false);
    assert(listener);

    /* insert 5 items at index 10 (out-of-bounds) */
    ret = vlc_playlist_RequestInsert(playlist, 10, &media[3], 2);
    assert(ret == VLC_SUCCESS);

    assert(vlc_playlist_Count(playlist) == 5);

    EXPECT_AT(0, 0);
    EXPECT_AT(1, 1);
    EXPECT_AT(2, 2);
    EXPECT_AT(3, 3);
    EXPECT_AT(4, 4);

    assert(ctx.vec_items_added.size == 1);
    assert(ctx.vec_items_added.data[0].index == 3); /* index was changed */
    assert(ctx.vec_items_added.data[0].count == 2);
    assert(ctx.vec_items_added.data[0].state.playlist_size == 5);

    callback_ctx_destroy(&ctx);
    vlc_playlist_RemoveListener(playlist, listener);
    DestroyMediaArray(media, 5);
    vlc_playlist_Delete(playlist);
}