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
struct wlr_box {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct sway_output {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  ly; int /*<<< orphan*/  lx; } ;

/* Variables and functions */

void output_get_box(struct sway_output *output, struct wlr_box *box) {
	box->x = output->lx;
	box->y = output->ly;
	box->width = output->width;
	box->height = output->height;
}