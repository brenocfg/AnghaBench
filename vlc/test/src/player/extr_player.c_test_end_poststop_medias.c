#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_player_t ;
struct TYPE_7__ {size_t size; scalar_t__* data; } ;
typedef  TYPE_3__ vec_on_current_media_changed ;
struct TYPE_6__ {size_t const size; scalar_t__* data; } ;
struct TYPE_5__ {TYPE_3__ on_current_media_changed; } ;
struct ctx {TYPE_2__ played_medias; int /*<<< orphan*/  wait; TYPE_1__ report; int /*<<< orphan*/ * player; } ;

/* Variables and functions */
 int /*<<< orphan*/ * VEC_LAST (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  player_set_current_mock_media (struct ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_player_CondWait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_player_GetCurrentMedia (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_end_poststop_medias(struct ctx *ctx)
{
    vlc_player_t *player = ctx->player;
    vec_on_current_media_changed *vec = &ctx->report.on_current_media_changed;

    assert(vec->size > 0);
    assert(vlc_player_GetCurrentMedia(player) != NULL);
    assert(VEC_LAST(vec) == vlc_player_GetCurrentMedia(player));
    const size_t oldsize = vec->size;

    player_set_current_mock_media(ctx, NULL, NULL, false);

    while (vec->size == oldsize)
        vlc_player_CondWait(player, &ctx->wait);

    assert(vec->size == ctx->played_medias.size);
    for (size_t i  = 0; i < vec->size; ++i)
        assert(vec->data[i] == ctx->played_medias.data[i]);

    assert(VEC_LAST(vec) == NULL);
    assert(vlc_player_GetCurrentMedia(player) == NULL);
}