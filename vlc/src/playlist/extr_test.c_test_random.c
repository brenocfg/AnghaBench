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
typedef  int /*<<< orphan*/  vlc_playlist_listener_id ;
struct vlc_playlist_callbacks {int /*<<< orphan*/  on_has_next_changed; int /*<<< orphan*/  on_has_prev_changed; int /*<<< orphan*/  on_current_index_changed; } ;
struct callback_ctx {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  selected ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 struct callback_ctx CALLBACK_CTX_INITIALIZER ; 
 int /*<<< orphan*/  CreateDummyMediaArray (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  DestroyMediaArray (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM ; 
 int /*<<< orphan*/  VLC_PLAYLIST_PLAYBACK_REPEAT_ALL ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  callback_ctx_destroy (struct callback_ctx*) ; 
 int /*<<< orphan*/  callback_on_current_index_changed ; 
 int /*<<< orphan*/  callback_on_has_next_changed ; 
 int /*<<< orphan*/  callback_on_has_prev_changed ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * vlc_playlist_AddListener (int /*<<< orphan*/ *,struct vlc_playlist_callbacks*,struct callback_ctx*,int) ; 
 int vlc_playlist_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int vlc_playlist_AppendOne (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_Delete (int /*<<< orphan*/ *) ; 
 int vlc_playlist_GetCurrentIndex (int /*<<< orphan*/ *) ; 
 int vlc_playlist_HasNext (int /*<<< orphan*/ *) ; 
 int vlc_playlist_HasPrev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_playlist_New (int /*<<< orphan*/ *) ; 
 int vlc_playlist_Next (int /*<<< orphan*/ *) ; 
 int vlc_playlist_Prev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_RemoveListener (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_playlist_RemoveOne (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_playlist_SetPlaybackOrder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_playlist_SetPlaybackRepeat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_random(void)
{
    vlc_playlist_t *playlist = vlc_playlist_New(NULL);
    assert(playlist);

    input_item_t *media[6];
    CreateDummyMediaArray(media, 6);

    /* initial playlist with 5 items (1 is not added immediately) */
    int ret = vlc_playlist_Append(playlist, media, 5);
    assert(ret == VLC_SUCCESS);

    struct vlc_playlist_callbacks cbs = {
        .on_current_index_changed = callback_on_current_index_changed,
        .on_has_prev_changed = callback_on_has_prev_changed,
        .on_has_next_changed = callback_on_has_next_changed,
    };

    struct callback_ctx ctx = CALLBACK_CTX_INITIALIZER;
    vlc_playlist_listener_id *listener =
            vlc_playlist_AddListener(playlist, &cbs, &ctx, false);
    assert(listener);

    assert(!vlc_playlist_HasPrev(playlist));
    assert(vlc_playlist_HasNext(playlist));

    for (int i = 0; i < 3; ++i)
    {
        assert(vlc_playlist_HasNext(playlist));
        ret = vlc_playlist_Next(playlist);
        assert(ret == VLC_SUCCESS);
    }

    assert(vlc_playlist_HasPrev(playlist));
    vlc_playlist_SetPlaybackOrder(playlist, VLC_PLAYLIST_PLAYBACK_ORDER_RANDOM);

    /* in random order, previous uses the history of randomly selected items */
    assert(!vlc_playlist_HasPrev(playlist));

    bool selected[5] = {};
    for (int i = 0; i < 5; ++i)
    {
        assert(vlc_playlist_HasNext(playlist));
        ret = vlc_playlist_Next(playlist);
        assert(ret == VLC_SUCCESS);
        ssize_t index = vlc_playlist_GetCurrentIndex(playlist);
        assert(index != -1);
        assert(!selected[index]); /* not selected twice */
        selected[index] = true;
    }

    assert(!vlc_playlist_HasNext(playlist));

    /* add a new item, it must be taken into account */
    ret = vlc_playlist_AppendOne(playlist, media[5]);
    assert(ret == VLC_SUCCESS);
    assert(vlc_playlist_HasNext(playlist));

    ret = vlc_playlist_Next(playlist);
    assert(ret == VLC_SUCCESS);

    assert(vlc_playlist_GetCurrentIndex(playlist) == 5);
    assert(!vlc_playlist_HasNext(playlist));

    vlc_playlist_RemoveOne(playlist, 5);

    /* enable repeat */
    vlc_playlist_SetPlaybackRepeat(playlist, VLC_PLAYLIST_PLAYBACK_REPEAT_ALL);

    /* now there are more items */
    assert(vlc_playlist_HasNext(playlist));

    /* once again */
    memset(selected, 0, sizeof(selected));
    for (int i = 0; i < 5; ++i)
    {
        assert(vlc_playlist_HasNext(playlist));
        ret = vlc_playlist_Next(playlist);
        assert(ret == VLC_SUCCESS);
        ssize_t index = vlc_playlist_GetCurrentIndex(playlist);
        assert(index != -1);
        assert(!selected[index]); /* not selected twice */
        selected[index] = true;
    }

    /* there are always more items */
    assert(vlc_playlist_HasNext(playlist));

    /* move to the middle of the random array */
    for (int i = 0; i < 3; ++i)
    {
        assert(vlc_playlist_HasNext(playlist));
        ret = vlc_playlist_Next(playlist);
        assert(ret == VLC_SUCCESS);
    }

    memset(selected, 0, sizeof(selected));
    int actual[5]; /* store the selected items (by their index) */

    ssize_t current = vlc_playlist_GetCurrentIndex(playlist);
    assert(current != -1);
    actual[4] = current;

    for (int i = 3; i >= 0; --i)
    {
        assert(vlc_playlist_HasPrev(playlist));
        ret = vlc_playlist_Prev(playlist);
        assert(ret == VLC_SUCCESS);
        ssize_t index = vlc_playlist_GetCurrentIndex(playlist);
        assert(index != -1);
        actual[i] = index;
        assert(!selected[index]); /* not selected twice */
        selected[index] = true;
    }

    /* no more previous, the history may only contain each item once */
    assert(!vlc_playlist_HasPrev(playlist));

    /* we should get the same items in the reverse order going forward */
    for (int i = 1; i < 5; ++i)
    {
        assert(vlc_playlist_HasNext(playlist));
        ret = vlc_playlist_Next(playlist);
        assert(ret == VLC_SUCCESS);
        ssize_t index = vlc_playlist_GetCurrentIndex(playlist);
        assert(index != -1);
        assert(index == actual[i]);
    }

    /* there are always more items */
    assert(vlc_playlist_HasNext(playlist));

    callback_ctx_destroy(&ctx);
    vlc_playlist_RemoveListener(playlist, listener);
    DestroyMediaArray(media, 6);
    vlc_playlist_Delete(playlist);
}