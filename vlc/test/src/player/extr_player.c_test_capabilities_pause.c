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
typedef  TYPE_2__ vec_on_capabilities_changed ;
struct media_params {int can_pause; } ;
struct TYPE_3__ {TYPE_2__ on_capabilities_changed; } ;
struct ctx {int /*<<< orphan*/  wait; TYPE_1__ report; int /*<<< orphan*/ * player; } ;

/* Variables and functions */
 struct media_params DEFAULT_MEDIA_PARAMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_PLAYER_STATE_STOPPED ; 
 int /*<<< orphan*/  VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  assert_normal_state (struct ctx*) ; 
 int /*<<< orphan*/  player_set_next_mock_media (struct ctx*,char*,struct media_params*) ; 
 int /*<<< orphan*/  player_start (struct ctx*) ; 
 int /*<<< orphan*/  test_end (struct ctx*) ; 
 int /*<<< orphan*/  test_log (char*) ; 
 int /*<<< orphan*/  test_prestop (struct ctx*) ; 
 int /*<<< orphan*/  vlc_player_ChangeRate (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  vlc_player_CondWait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_player_Pause (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_state (struct ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_capabilities_pause(struct ctx *ctx)
{
    test_log("capabilites_pause\n");
    vlc_player_t *player = ctx->player;

    struct media_params params = DEFAULT_MEDIA_PARAMS(VLC_TICK_FROM_SEC(1));
    params.can_pause = false;
    player_set_next_mock_media(ctx, "media1", &params);

    player_start(ctx);

    {
        vec_on_capabilities_changed *vec = &ctx->report.on_capabilities_changed;
        while (vec->size == 0)
            vlc_player_CondWait(player, &ctx->wait);
    }

    /* Ensure that pause doesn't work */
    vlc_player_Pause(player);
    vlc_player_ChangeRate(player, 32.f);

    test_prestop(ctx);

    wait_state(ctx, VLC_PLAYER_STATE_STOPPED);
    assert_normal_state(ctx);

    test_end(ctx);
}