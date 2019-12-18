#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_4__ {scalar_t__ size; } ;
typedef  TYPE_2__ vec_on_vout_changed ;
struct media_params {int dummy; } ;
struct TYPE_3__ {TYPE_2__ on_vout_changed; } ;
struct ctx {TYPE_1__ report; int /*<<< orphan*/ * player; } ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 struct media_params DEFAULT_MEDIA_PARAMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_PLAYER_STATE_STOPPING ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  player_set_current_mock_media (struct ctx*,char*,struct media_params*,int) ; 
 int /*<<< orphan*/  player_start (struct ctx*) ; 
 int /*<<< orphan*/  test_end (struct ctx*) ; 
 int /*<<< orphan*/  test_log (char*) ; 
 int /*<<< orphan*/ * vlc_player_aout_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_state (struct ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_no_outputs(struct ctx *ctx)
{
    test_log("test_no_outputs\n");
    vlc_player_t *player = ctx->player;

    struct media_params params = DEFAULT_MEDIA_PARAMS(VLC_TICK_FROM_MS(10));
    player_set_current_mock_media(ctx, "media1", &params, false);
    player_start(ctx);

    wait_state(ctx, VLC_PLAYER_STATE_STOPPING);
    {
        vec_on_vout_changed *vec = &ctx->report.on_vout_changed;
        assert(vec->size == 0);
    }

    audio_output_t *aout = vlc_player_aout_Hold(player);
    assert(!aout);

    test_end(ctx);
}