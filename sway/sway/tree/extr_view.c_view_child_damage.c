#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sway_view_child {TYPE_3__* view; int /*<<< orphan*/  surface; TYPE_1__* impl; int /*<<< orphan*/  mapped; } ;
struct TYPE_6__ {TYPE_2__* container; } ;
struct TYPE_5__ {scalar_t__ content_y; scalar_t__ content_x; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_root_coords ) (struct sway_view_child*,int*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  desktop_damage_surface (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (struct sway_view_child*,int*,int*) ; 

__attribute__((used)) static void view_child_damage(struct sway_view_child *child, bool whole) {
	if (!child || !child->mapped || !child->view || !child->view->container) {
		return;
	}
	int sx, sy;
	child->impl->get_root_coords(child, &sx, &sy);
	desktop_damage_surface(child->surface,
			child->view->container->content_x + sx,
			child->view->container->content_y + sy, whole);
}