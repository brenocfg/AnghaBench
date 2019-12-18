#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_playlist_t ;
typedef  int /*<<< orphan*/  vlc_playlist_listener_id ;
struct vlc_playlist_callbacks {int /*<<< orphan*/  on_has_next_changed; int /*<<< orphan*/  on_has_prev_changed; int /*<<< orphan*/  on_current_index_changed; int /*<<< orphan*/  on_playback_order_changed; int /*<<< orphan*/  on_playback_repeat_changed; int /*<<< orphan*/  on_items_reset; } ;
struct TYPE_15__ {int size; TYPE_11__* data; } ;
struct TYPE_13__ {int size; TYPE_9__* data; } ;
struct TYPE_23__ {int size; TYPE_7__* data; } ;
struct TYPE_21__ {int size; TYPE_5__* data; } ;
struct TYPE_19__ {int size; TYPE_3__* data; } ;
struct TYPE_17__ {int size; TYPE_1__* data; } ;
struct callback_ctx {TYPE_12__ vec_has_next_changed; TYPE_10__ vec_has_prev_changed; TYPE_8__ vec_current_index_changed; TYPE_6__ vec_playback_order_changed; TYPE_4__ vec_playback_repeat_changed; TYPE_2__ vec_items_reset; } ;
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_24__ {int has_prev; } ;
struct TYPE_22__ {int current; } ;
struct TYPE_20__ {scalar_t__ order; } ;
struct TYPE_18__ {scalar_t__ repeat; } ;
struct TYPE_16__ {int count; } ;
struct TYPE_14__ {int has_next; } ;

/* Variables and functions */
 struct callback_ctx CALLBACK_CTX_INITIALIZER ; 
 int /*<<< orphan*/  CreateDummyMediaArray (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  DestroyMediaArray (int /*<<< orphan*/ **,int) ; 
 scalar_t__ VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL ; 
 scalar_t__ VLC_PLAYLIST_PLAYBACK_REPEAT_ALL ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  callback_ctx_destroy (struct callback_ctx*) ; 
 int /*<<< orphan*/  callback_on_current_index_changed ; 
 int /*<<< orphan*/  callback_on_has_next_changed ; 
 int /*<<< orphan*/  callback_on_has_prev_changed ; 
 int /*<<< orphan*/  callback_on_items_reset ; 
 int /*<<< orphan*/  callback_on_playback_order_changed ; 
 int /*<<< orphan*/  callback_on_playback_repeat_changed ; 
 int /*<<< orphan*/ * vlc_playlist_AddListener (int /*<<< orphan*/ *,struct vlc_playlist_callbacks*,struct callback_ctx*,int) ; 
 int vlc_playlist_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  vlc_playlist_Delete (int /*<<< orphan*/ *) ; 
 int vlc_playlist_GoTo (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vlc_playlist_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_RemoveListener (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_SetPlaybackOrder (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vlc_playlist_SetPlaybackRepeat (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
test_callbacks_on_add_listener(void)
{
    vlc_playlist_t *playlist = vlc_playlist_New(NULL);
    assert(playlist);

    input_item_t *media[10];
    CreateDummyMediaArray(media, 10);

    /* initial playlist with 10 items */
    int ret = vlc_playlist_Append(playlist, media, 10);
    assert(ret == VLC_SUCCESS);

    vlc_playlist_SetPlaybackRepeat(playlist, VLC_PLAYLIST_PLAYBACK_REPEAT_ALL);
    vlc_playlist_SetPlaybackOrder(playlist, VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL);

    ret = vlc_playlist_GoTo(playlist, 5);
    assert(ret == VLC_SUCCESS);

    struct vlc_playlist_callbacks cbs = {
        .on_items_reset = callback_on_items_reset,
        .on_playback_repeat_changed = callback_on_playback_repeat_changed,
        .on_playback_order_changed = callback_on_playback_order_changed,
        .on_current_index_changed = callback_on_current_index_changed,
        .on_has_prev_changed = callback_on_has_prev_changed,
        .on_has_next_changed = callback_on_has_next_changed,
    };

    struct callback_ctx ctx = CALLBACK_CTX_INITIALIZER;
    vlc_playlist_listener_id *listener =
            vlc_playlist_AddListener(playlist, &cbs, &ctx, true);
    assert(listener);

    assert(ctx.vec_items_reset.size == 1);
    assert(ctx.vec_items_reset.data[0].count == 10);

    assert(ctx.vec_playback_repeat_changed.size == 1);
    assert(ctx.vec_playback_repeat_changed.data[0].repeat ==
                                            VLC_PLAYLIST_PLAYBACK_REPEAT_ALL);

    assert(ctx.vec_playback_order_changed.size == 1);
    assert(ctx.vec_playback_order_changed.data[0].order ==
                                            VLC_PLAYLIST_PLAYBACK_ORDER_NORMAL);

    assert(ctx.vec_current_index_changed.size == 1);
    assert(ctx.vec_current_index_changed.data[0].current == 5);

    assert(ctx.vec_has_prev_changed.size == 1);
    assert(ctx.vec_has_prev_changed.data[0].has_prev);

    assert(ctx.vec_has_next_changed.size == 1);
    assert(ctx.vec_has_next_changed.data[0].has_next);

    callback_ctx_destroy(&ctx);
    vlc_playlist_RemoveListener(playlist, listener);
    DestroyMediaArray(media, 10);
    vlc_playlist_Delete(playlist);
}