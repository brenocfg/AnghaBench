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
struct TYPE_4__ {int /*<<< orphan*/  error; } ;
struct TYPE_3__ {int /*<<< orphan*/  on_state_changed; } ;
struct ctx {TYPE_2__ params; TYPE_1__ report; int /*<<< orphan*/ * player; } ;

/* Variables and functions */
 scalar_t__ VEC_LAST (int /*<<< orphan*/ *) ; 
 scalar_t__ VLC_PLAYER_STATE_STOPPED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctx_reset (struct ctx*) ; 
 int /*<<< orphan*/  player_set_rate (struct ctx*,float) ; 
 int /*<<< orphan*/  test_end_poststop_medias (struct ctx*) ; 
 int /*<<< orphan*/  test_end_poststop_programs (struct ctx*) ; 
 int /*<<< orphan*/  test_end_poststop_state (struct ctx*) ; 
 int /*<<< orphan*/  test_end_poststop_titles (struct ctx*) ; 
 int /*<<< orphan*/  test_end_poststop_tracks (struct ctx*) ; 
 int /*<<< orphan*/  test_end_poststop_vouts (struct ctx*) ; 
 int /*<<< orphan*/ * vlc_player_GetCurrentMedia (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_SetStartPaused (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_player_Stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_state (struct ctx*,scalar_t__) ; 

__attribute__((used)) static void
test_end(struct ctx *ctx)
{
    vlc_player_t *player = ctx->player;

    /* Don't wait if we already stopped or waited for a stop */
    const bool wait_stopped =
        VEC_LAST(&ctx->report.on_state_changed) != VLC_PLAYER_STATE_STOPPED;
    /* Can be no-op */
    vlc_player_Stop(player);
    assert(vlc_player_GetCurrentMedia(player) != NULL);
    if (wait_stopped)
        wait_state(ctx, VLC_PLAYER_STATE_STOPPED);

    if (!ctx->params.error)
    {
        test_end_poststop_state(ctx);
        test_end_poststop_tracks(ctx);
        test_end_poststop_programs(ctx);
        test_end_poststop_titles(ctx);
        test_end_poststop_vouts(ctx);
    }
    test_end_poststop_medias(ctx);

    player_set_rate(ctx, 1.0f);
    vlc_player_SetStartPaused(player, false);

    ctx_reset(ctx);
}