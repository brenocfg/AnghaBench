#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  chain; int /*<<< orphan*/  ctx; int /*<<< orphan*/  gctx; scalar_t__ page; } ;
typedef  TYPE_1__ fz_jbig2d ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_jbig2_globals (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  jbig2_ctx_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbig2_release_page (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
close_jbig2d(fz_context *ctx, void *state_)
{
	fz_jbig2d *state = state_;
	if (state->page)
		jbig2_release_page(state->ctx, state->page);
	fz_drop_jbig2_globals(ctx, state->gctx);
	jbig2_ctx_free(state->ctx);
	fz_drop_stream(ctx, state->chain);
	fz_free(ctx, state);
}