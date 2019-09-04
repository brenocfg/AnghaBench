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
struct wlr_box {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct sway_output {int /*<<< orphan*/  damage; TYPE_1__* wlr_output; scalar_t__ ly; scalar_t__ lx; } ;
struct TYPE_2__ {int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct wlr_box*,struct wlr_box*,int) ; 
 int /*<<< orphan*/  scale_box (struct wlr_box*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_output_damage_add_box (int /*<<< orphan*/ ,struct wlr_box*) ; 

void output_damage_box(struct sway_output *output, struct wlr_box *_box) {
	struct wlr_box box;
	memcpy(&box, _box, sizeof(struct wlr_box));
	box.x -= output->lx;
	box.y -= output->ly;
	scale_box(&box, output->wlr_output->scale);
	wlr_output_damage_add_box(output->damage, &box);
}