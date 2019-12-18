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
struct TYPE_5__ {scalar_t__ size; } ;
typedef  TYPE_2__ vec_on_error_changed ;
struct media_params {int error; } ;
struct TYPE_4__ {TYPE_2__ on_error_changed; } ;
struct ctx {int /*<<< orphan*/  wait; TYPE_1__ report; int /*<<< orphan*/ * player; } ;

/* Variables and functions */
 struct media_params DEFAULT_MEDIA_PARAMS (int /*<<< orphan*/ ) ; 
 scalar_t__ VEC_LAST (TYPE_2__*) ; 
 scalar_t__ VLC_PLAYER_ERROR_NONE ; 
 int /*<<< orphan*/  VLC_PLAYER_STATE_STOPPED ; 
 int /*<<< orphan*/  VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  player_set_next_mock_media (struct ctx*,char*,struct media_params*) ; 
 int /*<<< orphan*/  player_start (struct ctx*) ; 
 int /*<<< orphan*/  test_end (struct ctx*) ; 
 int /*<<< orphan*/  test_log (char*) ; 
 int /*<<< orphan*/  vlc_player_CondWait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_state (struct ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_error(struct ctx *ctx)
{
    test_log("error\n");
    vlc_player_t *player = ctx->player;

    struct media_params params = DEFAULT_MEDIA_PARAMS(VLC_TICK_FROM_SEC(1));
    params.error = true;
    player_set_next_mock_media(ctx, "media1", &params);

    player_start(ctx);

    {
        vec_on_error_changed *vec = &ctx->report.on_error_changed;
        while (vec->size == 0 || VEC_LAST(vec) == VLC_PLAYER_ERROR_NONE)
            vlc_player_CondWait(player, &ctx->wait);
    }
    wait_state(ctx, VLC_PLAYER_STATE_STOPPED);

    test_end(ctx);
}