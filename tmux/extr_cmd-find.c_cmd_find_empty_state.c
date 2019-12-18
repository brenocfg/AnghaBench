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
struct cmd_find_state {int /*<<< orphan*/ * wp; int /*<<< orphan*/ * w; int /*<<< orphan*/ * wl; int /*<<< orphan*/ * s; } ;

/* Variables and functions */

int
cmd_find_empty_state(struct cmd_find_state *fs)
{
	if (fs->s == NULL && fs->wl == NULL && fs->w == NULL && fs->wp == NULL)
		return (1);
	return (0);
}