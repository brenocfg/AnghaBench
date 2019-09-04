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
typedef  int /*<<< orphan*/  u_char ;
struct screen_write_ctx {int dummy; } ;
struct grid_cell {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct grid_cell*,struct grid_cell const*,int) ; 
 int /*<<< orphan*/  screen_write_cell (struct screen_write_ctx*,struct grid_cell*) ; 
 int /*<<< orphan*/  utf8_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
screen_write_putc(struct screen_write_ctx *ctx, const struct grid_cell *gcp,
    u_char ch)
{
	struct grid_cell	gc;

	memcpy(&gc, gcp, sizeof gc);

	utf8_set(&gc.data, ch);
	screen_write_cell(ctx, &gc);
}