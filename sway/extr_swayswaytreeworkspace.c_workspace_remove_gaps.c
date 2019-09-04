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
struct TYPE_2__ {scalar_t__ top; scalar_t__ right; scalar_t__ bottom; scalar_t__ left; } ;
struct sway_workspace {TYPE_1__ current_gaps; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */

void workspace_remove_gaps(struct sway_workspace *ws) {
	if (ws->current_gaps.top == 0 && ws->current_gaps.right == 0 &&
			ws->current_gaps.bottom == 0 && ws->current_gaps.left == 0) {
		return;
	}

	ws->width += ws->current_gaps.left + ws->current_gaps.right;
	ws->height += ws->current_gaps.top + ws->current_gaps.bottom;
	ws->x -= ws->current_gaps.left;
	ws->y -= ws->current_gaps.top;

	ws->current_gaps.top = 0;
	ws->current_gaps.right = 0;
	ws->current_gaps.bottom = 0;
	ws->current_gaps.left = 0;
}