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
struct tty_ctx {int /*<<< orphan*/  num; int /*<<< orphan*/  ptr; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_add (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_invalidate (struct tty*) ; 

void
tty_cmd_rawstring(struct tty *tty, const struct tty_ctx *ctx)
{
	tty_add(tty, ctx->ptr, ctx->num);
	tty_invalidate(tty);
}