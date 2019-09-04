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
struct screen_write_ctx {struct screen* s; } ;
struct screen {int /*<<< orphan*/  mode; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
struct input_ctx {int /*<<< orphan*/  old_mode; int /*<<< orphan*/  old_cy; int /*<<< orphan*/  old_cx; int /*<<< orphan*/  cell; int /*<<< orphan*/  old_cell; struct screen_write_ctx ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
input_save_state(struct input_ctx *ictx)
{
	struct screen_write_ctx	*sctx = &ictx->ctx;
	struct screen		*s = sctx->s;

	memcpy(&ictx->old_cell, &ictx->cell, sizeof ictx->old_cell);
	ictx->old_cx = s->cx;
	ictx->old_cy = s->cy;
	ictx->old_mode = s->mode;
}