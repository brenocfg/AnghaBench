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
struct sway_workspace {double x; double width; double y; double height; } ;
struct sway_cursor {int /*<<< orphan*/  cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlr_cursor_warp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,double,double) ; 

void cursor_warp_to_workspace(struct sway_cursor *cursor,
		struct sway_workspace *workspace) {
	if (!workspace) {
		return;
	}

	double x = workspace->x + workspace->width / 2.0;
	double y = workspace->y + workspace->height / 2.0;

	wlr_cursor_warp(cursor->cursor, NULL, x, y);
}