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
typedef  int /*<<< orphan*/  vlc_player_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct media_params {int dummy; } ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 struct media_params DEFAULT_MEDIA_PARAMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_PLAYER_LOCK_NORMAL ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * create_mock_media (char*,struct media_params*) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_log (char*,int) ; 
 int /*<<< orphan*/  vlc_player_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_player_New (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlc_player_SetCurrentMedia (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlc_player_Start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_delete_while_playback(vlc_object_t *obj, bool start)
{
    test_log("delete_while_playback (start: %d)\n", start);
    vlc_player_t *player = vlc_player_New(obj, VLC_PLAYER_LOCK_NORMAL,
                                          NULL, NULL);

    struct media_params params = DEFAULT_MEDIA_PARAMS(VLC_TICK_FROM_SEC(10));
    input_item_t *media = create_mock_media("media1", &params);
    assert(media);

    vlc_player_Lock(player);
    int ret = vlc_player_SetCurrentMedia(player, media);
    assert(ret == VLC_SUCCESS);
    input_item_Release(media);

    if (start)
    {
        ret = vlc_player_Start(player);
        assert(ret == VLC_SUCCESS);
    }

    vlc_player_Unlock(player);

    vlc_player_Delete(player);
}