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
typedef  int /*<<< orphan*/  u_int ;
struct tty_ctx {int /*<<< orphan*/  wp; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 scalar_t__ tty_clamp_area (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_clear_area (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tty_clear_pane_area(struct tty *tty, const struct tty_ctx *ctx, u_int py,
    u_int ny, u_int px, u_int nx, u_int bg)
{
	u_int	i, j, x, y, rx, ry;

	if (tty_clamp_area(tty, ctx, px, py, nx, ny, &i, &j, &x, &y, &rx, &ry))
		tty_clear_area(tty, ctx->wp, y, ry, x, rx, bg);
}