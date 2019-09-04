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
struct screen {struct grid* grid; } ;
struct grid {scalar_t__ hsize; scalar_t__ hscrolled; int /*<<< orphan*/  sy; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_move_lines (struct grid*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

void
screen_write_clearhistory(struct screen_write_ctx *ctx)
{
	struct screen	*s = ctx->s;
	struct grid	*gd = s->grid;

	grid_move_lines(gd, 0, gd->hsize, gd->sy, 8);
	gd->hscrolled = gd->hsize = 0;
}