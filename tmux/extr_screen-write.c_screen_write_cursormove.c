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
typedef  scalar_t__ u_int ;
struct screen_write_ctx {struct screen* s; } ;
struct screen {int mode; int rlower; scalar_t__ rupper; } ;

/* Variables and functions */
 int MODE_ORIGIN ; 
 int screen_size_x (struct screen*) ; 
 int screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  screen_write_set_cursor (struct screen_write_ctx*,int,int) ; 

void
screen_write_cursormove(struct screen_write_ctx *ctx, int px, int py,
    int origin)
{
	struct screen	*s = ctx->s;

	if (origin && py != -1 && (s->mode & MODE_ORIGIN)) {
		if ((u_int)py > s->rlower - s->rupper)
			py = s->rlower;
		else
			py += s->rupper;
	}

	if (px != -1 && (u_int)px > screen_size_x(s) - 1)
		px = screen_size_x(s) - 1;
	if (py != -1 && (u_int)py > screen_size_y(s) - 1)
		py = screen_size_y(s) - 1;

	screen_write_set_cursor(ctx, px, py);
}