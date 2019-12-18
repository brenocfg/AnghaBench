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
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_6__ {int size; scalar_t__* data; } ;
typedef  TYPE_3__ vec_on_error_changed ;
struct TYPE_5__ {TYPE_3__ on_error_changed; } ;
struct TYPE_4__ {int error; } ;
struct ctx {TYPE_2__ report; int /*<<< orphan*/  played_medias; TYPE_1__ params; int /*<<< orphan*/ * player; } ;
typedef  int /*<<< orphan*/  input_item_t ;

/* Variables and functions */
 scalar_t__ VLC_PLAYER_ERROR_NONE ; 
 int /*<<< orphan*/  VLC_PLAYER_STATE_STARTED ; 
 int /*<<< orphan*/  VLC_PLAYER_STATE_STOPPED ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * input_item_New (char*,char*) ; 
 int /*<<< orphan*/  player_start (struct ctx*) ; 
 int /*<<< orphan*/  test_end (struct ctx*) ; 
 int /*<<< orphan*/  test_log (char*) ; 
 int vlc_player_SetCurrentMedia (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlc_vector_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_state (struct ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_unknown_uri(struct ctx *ctx)
{
    test_log("unknown_uri");
    vlc_player_t *player = ctx->player;

    input_item_t *media = input_item_New("unknownuri://foo", "fail");
    assert(media);
    int ret = vlc_player_SetCurrentMedia(player, media);
    assert(ret == VLC_SUCCESS);

    ctx->params.error = true;
    bool success = vlc_vector_push(&ctx->played_medias, media);
    assert(success);

    player_start(ctx);

    wait_state(ctx, VLC_PLAYER_STATE_STARTED);
    wait_state(ctx, VLC_PLAYER_STATE_STOPPED);
    {
        vec_on_error_changed *vec = &ctx->report.on_error_changed;
        assert(vec->size == 1);
        assert(vec->data[0] != VLC_PLAYER_ERROR_NONE);
    }

    test_end(ctx);
}