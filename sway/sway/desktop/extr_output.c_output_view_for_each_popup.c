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
typedef  int /*<<< orphan*/  sway_surface_iterator_func_t ;
struct TYPE_3__ {scalar_t__ y; scalar_t__ x; } ;
struct sway_view {TYPE_2__* container; TYPE_1__ geometry; } ;
struct sway_output {scalar_t__ ly; scalar_t__ lx; } ;
struct surface_iterator_data {void* user_data; int /*<<< orphan*/  rotation; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ oy; scalar_t__ ox; struct sway_output* output; int /*<<< orphan*/  user_iterator; } ;
struct TYPE_4__ {int /*<<< orphan*/  surface_height; int /*<<< orphan*/  surface_width; scalar_t__ surface_y; scalar_t__ surface_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  output_for_each_surface_iterator ; 
 int /*<<< orphan*/  view_for_each_popup (struct sway_view*,int /*<<< orphan*/ ,struct surface_iterator_data*) ; 

void output_view_for_each_popup(struct sway_output *output,
		struct sway_view *view, sway_surface_iterator_func_t iterator,
		void *user_data) {
	struct surface_iterator_data data = {
		.user_iterator = iterator,
		.user_data = user_data,
		.output = output,
		.ox = view->container->surface_x - output->lx
			- view->geometry.x,
		.oy = view->container->surface_y - output->ly
			- view->geometry.y,
		.width = view->container->surface_width,
		.height = view->container->surface_height,
		.rotation = 0, // TODO
	};

	view_for_each_popup(view, output_for_each_surface_iterator, &data);
}