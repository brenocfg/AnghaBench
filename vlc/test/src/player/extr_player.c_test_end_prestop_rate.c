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
struct TYPE_5__ {scalar_t__ size; } ;
typedef  TYPE_2__ vec_on_rate_changed ;
struct TYPE_4__ {TYPE_2__ on_rate_changed; } ;
struct ctx {float rate; int /*<<< orphan*/  wait; int /*<<< orphan*/  player; TYPE_1__ report; } ;

/* Variables and functions */
 float VEC_LAST (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_player_CondWait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_end_prestop_rate(struct ctx *ctx)
{
    if (ctx->rate != 1.0f)
    {
        vec_on_rate_changed *vec = &ctx->report.on_rate_changed;
        while (vec->size == 0)
            vlc_player_CondWait(ctx->player, &ctx->wait);
        assert(vec->size > 0);
        assert(VEC_LAST(vec) == ctx->rate);
    }

}