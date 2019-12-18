#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ width; scalar_t__ height; } ;
struct wlr_surface {TYPE_3__ current; } ;
struct wlr_box {scalar_t__ width; scalar_t__ height; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_7__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_6__ {scalar_t__ y; scalar_t__ x; } ;
struct sway_view {scalar_t__ saved_buffer_width; scalar_t__ saved_buffer_height; struct wlr_surface* surface; TYPE_2__ geometry; scalar_t__ saved_buffer; TYPE_1__ saved_geometry; } ;
struct sway_container_state {int dummy; } ;
struct TYPE_9__ {int ntxnrefs; int /*<<< orphan*/  destroying; } ;
struct TYPE_10__ {scalar_t__ content_y; scalar_t__ content_x; int /*<<< orphan*/  children; } ;
struct sway_container {scalar_t__ width; int content_width; scalar_t__ height; int content_height; int surface_width; int surface_height; TYPE_4__ node; scalar_t__ content_y; scalar_t__ surface_y; scalar_t__ content_x; scalar_t__ surface_x; TYPE_5__ current; struct sway_view* view; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_discover_outputs (struct sway_container*) ; 
 int /*<<< orphan*/  desktop_damage_box (struct wlr_box*) ; 
 int /*<<< orphan*/  desktop_damage_whole_container (struct sway_container*) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,struct sway_container_state*,int) ; 
 int /*<<< orphan*/  view_remove_saved_buffer (struct sway_view*) ; 

__attribute__((used)) static void apply_container_state(struct sway_container *container,
		struct sway_container_state *state) {
	struct sway_view *view = container->view;
	// Damage the old location
	desktop_damage_whole_container(container);
	if (view && view->saved_buffer) {
		struct wlr_box box = {
			.x = container->current.content_x - view->saved_geometry.x,
			.y = container->current.content_y - view->saved_geometry.y,
			.width = view->saved_buffer_width,
			.height = view->saved_buffer_height,
		};
		desktop_damage_box(&box);
	}

	// There are separate children lists for each instruction state, the
	// container's current state and the container's pending state
	// (ie. con->children). The list itself needs to be freed here.
	// Any child containers which are being deleted will be cleaned up in
	// transaction_destroy().
	list_free(container->current.children);

	memcpy(&container->current, state, sizeof(struct sway_container_state));

	if (view && view->saved_buffer) {
		if (!container->node.destroying || container->node.ntxnrefs == 1) {
			view_remove_saved_buffer(view);
		}
	}

	// Damage the new location
	desktop_damage_whole_container(container);
	if (view && view->surface) {
		struct wlr_surface *surface = view->surface;
		struct wlr_box box = {
			.x = container->current.content_x - view->geometry.x,
			.y = container->current.content_y - view->geometry.y,
			.width = surface->current.width,
			.height = surface->current.height,
		};
		desktop_damage_box(&box);
	}

	// If the view hasn't responded to the configure, center it within
	// the container. This is important for fullscreen views which
	// refuse to resize to the size of the output.
	if (view && view->surface) {
		if (view->surface->current.width < container->width) {
			container->surface_x = container->content_x +
				(container->content_width - view->surface->current.width) / 2;
		} else {
			container->surface_x = container->content_x;
		}
		if (view->surface->current.height < container->height) {
			container->surface_y = container->content_y +
				(container->content_height - view->surface->current.height) / 2;
		} else {
			container->surface_y = container->content_y;
		}
		container->surface_width = view->surface->current.width;
		container->surface_height = view->surface->current.height;
	}

	if (!container->node.destroying) {
		container_discover_outputs(container);
	}
}