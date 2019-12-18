#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t const size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_4__ vec_on_current_media_changed ;
struct media_params {int dummy; } ;
struct TYPE_7__ {size_t size; } ;
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_5__ {TYPE_4__ on_current_media_changed; } ;
struct ctx {TYPE_3__ played_medias; TYPE_2__ next_medias; TYPE_1__ report; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
 struct media_params DEFAULT_MEDIA_PARAMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_PLAYER_STATE_STOPPED ; 
 int /*<<< orphan*/  VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_media_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  assert_normal_state (struct ctx*) ; 
 int /*<<< orphan*/  player_set_next_mock_media (struct ctx*,char const*,struct media_params*) ; 
 int /*<<< orphan*/  player_set_rate (struct ctx*,float) ; 
 int /*<<< orphan*/  player_start (struct ctx*) ; 
 int /*<<< orphan*/  test_end (struct ctx*) ; 
 int /*<<< orphan*/  test_log (char*) ; 
 int /*<<< orphan*/  test_prestop (struct ctx*) ; 
 int /*<<< orphan*/  wait_state (struct ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_next_media(struct ctx *ctx)
{
    test_log("next_media\n");
    const char *media_names[] = { "media1", "media2", "media3" };
    const size_t media_count = ARRAY_SIZE(media_names);

    struct media_params params = DEFAULT_MEDIA_PARAMS(VLC_TICK_FROM_MS(100));

    for (size_t i = 0; i < media_count; ++i)
        player_set_next_mock_media(ctx, media_names[i], &params);
    player_set_rate(ctx, 4.f);
    player_start(ctx);

    test_prestop(ctx);
    wait_state(ctx, VLC_PLAYER_STATE_STOPPED);
    assert_normal_state(ctx);

    {
        vec_on_current_media_changed *vec = &ctx->report.on_current_media_changed;

        assert(vec->size == media_count);
        assert(ctx->next_medias.size == 0);
        for (size_t i = 0; i < ctx->played_medias.size; ++i)
            assert_media_name(vec->data[i], media_names[i]);
    }

    test_end(ctx);
}