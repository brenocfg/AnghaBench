#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double x; double y; } ;
struct sway_view {int /*<<< orphan*/  surface; TYPE_2__ geometry; TYPE_1__* container; } ;
struct sway_output {double lx; double ly; } ;
struct render_data {float alpha; int /*<<< orphan*/ * damage; } ;
typedef  int /*<<< orphan*/  pixman_region32_t ;
struct TYPE_3__ {double surface_x; double surface_y; } ;

/* Variables and functions */
 int /*<<< orphan*/  output_surface_for_each_surface (struct sway_output*,int /*<<< orphan*/ ,double,double,int /*<<< orphan*/ ,struct render_data*) ; 
 int /*<<< orphan*/  render_surface_iterator ; 

__attribute__((used)) static void render_view_toplevels(struct sway_view *view,
		struct sway_output *output, pixman_region32_t *damage, float alpha) {
	struct render_data data = {
		.damage = damage,
		.alpha = alpha,
	};
	// Render all toplevels without descending into popups
	double ox = view->container->surface_x -
		output->lx - view->geometry.x;
	double oy = view->container->surface_y -
		output->ly - view->geometry.y;
	output_surface_for_each_surface(output, view->surface, ox, oy,
			render_surface_iterator, &data);
}