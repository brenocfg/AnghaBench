#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct window_pane {int /*<<< orphan*/  base; int /*<<< orphan*/  modes; struct input_ctx* ictx; } ;
struct screen_write_ctx {int dummy; } ;
struct input_ctx {int last; scalar_t__ flags; int /*<<< orphan*/ * state; struct screen_write_ctx ctx; } ;

/* Variables and functions */
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_clear (struct input_ctx*) ; 
 int /*<<< orphan*/  input_reset_cell (struct input_ctx*) ; 
 int /*<<< orphan*/  input_state_ground ; 
 int /*<<< orphan*/  screen_write_reset (struct screen_write_ctx*) ; 
 int /*<<< orphan*/  screen_write_start (struct screen_write_ctx*,struct window_pane*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screen_write_stop (struct screen_write_ctx*) ; 

void
input_reset(struct window_pane *wp, int clear)
{
	struct input_ctx	*ictx = wp->ictx;
	struct screen_write_ctx	*sctx = &ictx->ctx;

	input_reset_cell(ictx);

	if (clear) {
		if (TAILQ_EMPTY(&wp->modes))
			screen_write_start(sctx, wp, &wp->base);
		else
			screen_write_start(sctx, NULL, &wp->base);
		screen_write_reset(sctx);
		screen_write_stop(sctx);
	}

	input_clear(ictx);

	ictx->last = -1;

	ictx->state = &input_state_ground;
	ictx->flags = 0;
}