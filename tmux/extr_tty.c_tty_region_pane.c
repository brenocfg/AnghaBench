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
struct tty_ctx {scalar_t__ oy; scalar_t__ yoff; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_region (struct tty*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
tty_region_pane(struct tty *tty, const struct tty_ctx *ctx, u_int rupper,
    u_int rlower)
{
	tty_region(tty, ctx->yoff + rupper - ctx->oy,
	    ctx->yoff + rlower - ctx->oy);
}