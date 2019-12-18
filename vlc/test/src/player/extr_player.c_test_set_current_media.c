#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_5__ {int size; } ;
typedef  TYPE_2__ vec_on_current_media_changed ;
struct media_params {int dummy; } ;
struct TYPE_4__ {TYPE_2__ on_current_media_changed; } ;
struct ctx {TYPE_2__ played_medias; int /*<<< orphan*/  extra_start_count; int /*<<< orphan*/  wait; TYPE_1__ report; int /*<<< orphan*/ * player; } ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 struct media_params DEFAULT_MEDIA_PARAMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * VEC_LAST (TYPE_2__*) ; 
 int /*<<< orphan*/  VLC_PLAYER_STATE_PLAYING ; 
 int /*<<< orphan*/  VLC_PLAYER_STATE_STARTED ; 
 int /*<<< orphan*/  VLC_PLAYER_STATE_STOPPED ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_media_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  assert_normal_state (struct ctx*) ; 
 int /*<<< orphan*/  player_set_current_mock_media (struct ctx*,char const*,struct media_params*,int) ; 
 int /*<<< orphan*/  player_start (struct ctx*) ; 
 int /*<<< orphan*/  test_end (struct ctx*) ; 
 int /*<<< orphan*/  test_log (char*) ; 
 int /*<<< orphan*/  test_prestop (struct ctx*) ; 
 int /*<<< orphan*/  vlc_player_CondWait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_player_GetCurrentMedia (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_state (struct ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_set_current_media(struct ctx *ctx)
{
    test_log("current_media\n");
    const char *media_names[] = { "media1", "media2", "media3" };
    const size_t media_count = ARRAY_SIZE(media_names);

    vlc_player_t *player = ctx->player;
    struct media_params params = DEFAULT_MEDIA_PARAMS(VLC_TICK_FROM_MS(100));

    player_set_current_mock_media(ctx, media_names[0], &params, false);
    player_start(ctx);

    wait_state(ctx, VLC_PLAYER_STATE_PLAYING);

    /* Call vlc_player_SetCurrentMedia for the remaining medias interrupting
     * the player and without passing by the next_media provider. */
    {
        vec_on_current_media_changed *vec = &ctx->report.on_current_media_changed;
        assert(vec->size == 1);
        for (size_t i = 1; i <= media_count; ++i)
        {
            while (vec->size != i)
                vlc_player_CondWait(player, &ctx->wait);

            input_item_t *last_media = VEC_LAST(vec);
            assert(last_media);
            assert(last_media == vlc_player_GetCurrentMedia(player));
            assert(last_media == VEC_LAST(&ctx->played_medias));
            assert_media_name(last_media, media_names[i - 1]);

            if (i < media_count)
            {
                /* Next vlc_player_SetCurrentMedia() call should be
                 * asynchronous since we are still playing. Therefore,
                 * vlc_player_GetCurrentMedia() should return the last one. */
                player_set_current_mock_media(ctx, "ignored", &params, true);
                assert(vlc_player_GetCurrentMedia(player) == last_media);

                /* The previous media is ignored due to this call */
                player_set_current_mock_media(ctx, media_names[i], &params, false);
            }
        }
    }

    test_prestop(ctx);
    wait_state(ctx, VLC_PLAYER_STATE_STOPPED);
    assert_normal_state(ctx);

    /* Test that the player can be played again with the same media */
    player_start(ctx);
    ctx->extra_start_count++; /* Since we play the same media  */

    /* Current state is already stopped, wait first for started then */
    wait_state(ctx, VLC_PLAYER_STATE_STARTED);
    wait_state(ctx, VLC_PLAYER_STATE_STOPPED);

    assert_normal_state(ctx);

    /* Playback is stopped: vlc_player_SetCurrentMedia should be synchronous */
    player_set_current_mock_media(ctx, media_names[0], &params, false);
    assert(vlc_player_GetCurrentMedia(player) == VEC_LAST(&ctx->played_medias));

    player_start(ctx);

    wait_state(ctx, VLC_PLAYER_STATE_STARTED);
    wait_state(ctx, VLC_PLAYER_STATE_STOPPED);

    test_end(ctx);
}