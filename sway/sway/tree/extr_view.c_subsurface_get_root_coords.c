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
struct wlr_surface {int dummy; } ;
struct TYPE_9__ {scalar_t__ y; scalar_t__ x; } ;
struct wlr_subsurface {struct wlr_surface* parent; TYPE_4__ current; } ;
struct sway_view_child {TYPE_5__* parent; TYPE_2__* view; struct wlr_surface* surface; } ;
struct TYPE_10__ {TYPE_3__* impl; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* get_root_coords ) (TYPE_5__*,int*,int*) ;} ;
struct TYPE_6__ {int x; int y; } ;
struct TYPE_7__ {TYPE_1__ geometry; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_5__*,int*,int*) ; 
 struct wlr_subsurface* wlr_subsurface_from_wlr_surface (struct wlr_surface*) ; 
 scalar_t__ wlr_surface_is_subsurface (struct wlr_surface*) ; 

__attribute__((used)) static void subsurface_get_root_coords(struct sway_view_child *child,
		int *root_sx, int *root_sy) {
	struct wlr_surface *surface = child->surface;
	*root_sx = -child->view->geometry.x;
	*root_sy = -child->view->geometry.y;

	if (child->parent && child->parent->impl &&
			child->parent->impl->get_root_coords) {
		int sx, sy;
		child->parent->impl->get_root_coords(child->parent, &sx, &sy);
		*root_sx += sx;
		*root_sy += sy;
	} else {
		while (surface && wlr_surface_is_subsurface(surface)) {
			struct wlr_subsurface *subsurface =
				wlr_subsurface_from_wlr_surface(surface);
			if (subsurface == NULL) {
				break;
			}
			*root_sx += subsurface->current.x;
			*root_sy += subsurface->current.y;
			surface = subsurface->parent;
		}
	}
}