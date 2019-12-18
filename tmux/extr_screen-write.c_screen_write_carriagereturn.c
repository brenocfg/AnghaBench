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
struct screen_write_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  screen_write_set_cursor (struct screen_write_ctx*,int /*<<< orphan*/ ,int) ; 

void
screen_write_carriagereturn(struct screen_write_ctx *ctx)
{
	screen_write_set_cursor(ctx, 0, -1);
}