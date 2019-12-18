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
struct tty_ctx {int /*<<< orphan*/  orupper; int /*<<< orphan*/  orlower; int /*<<< orphan*/  ocy; int /*<<< orphan*/  ocx; int /*<<< orphan*/  wp; } ;
struct screen_write_ctx {int /*<<< orphan*/  wp; struct screen* s; } ;
struct screen {int /*<<< orphan*/  rupper; int /*<<< orphan*/  rlower; int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct tty_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
	struct screen	*s = ctx->s;

	memset(ttyctx, 0, sizeof *ttyctx);

	ttyctx->wp = ctx->wp;

	ttyctx->ocx = s->cx;
	ttyctx->ocy = s->cy;

	ttyctx->orlower = s->rlower;
	ttyctx->orupper = s->rupper;
}