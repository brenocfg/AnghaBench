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
struct tty_ctx {scalar_t__ oy; scalar_t__ yoff; scalar_t__ ox; scalar_t__ xoff; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_cursor (struct tty*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
tty_cursor_pane(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
	tty_cursor(tty, ctx->xoff + cx - ctx->ox, ctx->yoff + cy - ctx->oy);
}