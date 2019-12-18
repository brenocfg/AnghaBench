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
struct screen {int mode; } ;

/* Variables and functions */

void
screen_write_mode_set(struct screen_write_ctx *ctx, int mode)
{
	struct screen	*s = ctx->s;

	s->mode |= mode;
}