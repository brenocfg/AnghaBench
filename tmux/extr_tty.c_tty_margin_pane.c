#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_ctx {int xoff; int ox; TYPE_1__* wp; } ;
struct tty {int dummy; } ;
struct TYPE_2__ {int sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_margin (struct tty*,int,int) ; 

__attribute__((used)) static void
tty_margin_pane(struct tty *tty, const struct tty_ctx *ctx)
{
	tty_margin(tty, ctx->xoff - ctx->ox,
	    ctx->xoff + ctx->wp->sx - 1 - ctx->ox);
}