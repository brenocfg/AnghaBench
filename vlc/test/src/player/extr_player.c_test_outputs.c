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
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_6__ {int size; TYPE_2__* data; } ;
typedef  TYPE_3__ vec_on_vout_changed ;
struct media_params {int dummy; } ;
struct TYPE_4__ {TYPE_3__ on_vout_changed; } ;
struct ctx {TYPE_1__ report; int /*<<< orphan*/ * player; } ;
typedef  int /*<<< orphan*/  audio_output_t ;
struct TYPE_5__ {scalar_t__ action; int /*<<< orphan*/ * vout; } ;

/* Variables and functions */
 struct media_params DEFAULT_MEDIA_PARAMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_PLAYER_STATE_STOPPING ; 
 scalar_t__ VLC_PLAYER_VOUT_STARTED ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  aout_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  player_set_current_mock_media (struct ctx*,char*,struct media_params*,int) ; 
 int /*<<< orphan*/  player_start (struct ctx*) ; 
 int /*<<< orphan*/  test_end (struct ctx*) ; 
 int /*<<< orphan*/  test_log (char*) ; 
 int /*<<< orphan*/ * vlc_player_aout_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_player_vout_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** vlc_player_vout_HoldAll (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_state (struct ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_outputs(struct ctx *ctx)
{
    test_log("test_outputs\n");
    vlc_player_t *player = ctx->player;

    /* Test that the player has a valid aout and vout, even before first
     * playback */
    audio_output_t *aout = vlc_player_aout_Hold(player);
    assert(aout);

    vout_thread_t *vout = vlc_player_vout_Hold(player);
    assert(vout);

    size_t vout_count;
    vout_thread_t **vout_list = vlc_player_vout_HoldAll(player, &vout_count);
    assert(vout_count == 1 && vout_list[0] == vout);
    vout_Release(vout_list[0]);
    free(vout_list);
    vout_Release(vout);

    /* Test that the player keep the same aout and vout during playback */
    struct media_params params = DEFAULT_MEDIA_PARAMS(VLC_TICK_FROM_MS(10));

    player_set_current_mock_media(ctx, "media1", &params, false);
    player_start(ctx);

    wait_state(ctx, VLC_PLAYER_STATE_STOPPING);

    {
        vec_on_vout_changed *vec = &ctx->report.on_vout_changed;
        assert(vec->size >= 1);
        assert(vec->data[0].action == VLC_PLAYER_VOUT_STARTED);

        vout_thread_t *same_vout = vlc_player_vout_Hold(player);
        assert(vec->data[0].vout == same_vout);
        vout_Release(same_vout);
    }

    audio_output_t *same_aout = vlc_player_aout_Hold(player);
    assert(same_aout == aout);
    aout_Release(same_aout);

    aout_Release(aout);
    test_end(ctx);
}