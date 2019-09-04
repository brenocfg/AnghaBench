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
struct cmd_find_state {int /*<<< orphan*/  wp; int /*<<< orphan*/  w; int /*<<< orphan*/  idx; int /*<<< orphan*/  wl; int /*<<< orphan*/  s; } ;

/* Variables and functions */

void
cmd_find_copy_state(struct cmd_find_state *dst, struct cmd_find_state *src)
{
	dst->s = src->s;
	dst->wl = src->wl;
	dst->idx = src->idx;
	dst->w = src->w;
	dst->wp = src->wp;
}