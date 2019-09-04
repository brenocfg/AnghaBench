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
struct wlr_box {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_8__ {scalar_t__ y; scalar_t__ x; } ;
struct sway_view {TYPE_2__* surface; TYPE_3__ geometry; TYPE_5__* container; } ;
struct TYPE_9__ {scalar_t__ content_y; scalar_t__ content_x; } ;
struct TYPE_10__ {TYPE_4__ current; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_7__ {TYPE_1__ current; } ;

/* Variables and functions */
 int /*<<< orphan*/  desktop_damage_box (struct wlr_box*) ; 
 int /*<<< orphan*/  desktop_damage_whole_container (TYPE_5__*) ; 

void desktop_damage_view(struct sway_view *view) {
	desktop_damage_whole_container(view->container);
	struct wlr_box box = {
		.x = view->container->current.content_x - view->geometry.x,
		.y = view->container->current.content_y - view->geometry.y,
		.width = view->surface->current.width,
		.height = view->surface->current.height,
	};
	desktop_damage_box(&box);
}