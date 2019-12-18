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
struct sway_view {struct sway_container* container; } ;
struct TYPE_2__ {int content_width; int content_height; } ;
struct sway_container {int content_width; int content_height; int surface_width; int surface_height; void* content_y; void* surface_y; void* content_x; void* surface_x; TYPE_1__ current; } ;

/* Variables and functions */
 scalar_t__ container_is_floating (struct sway_container*) ; 
 int /*<<< orphan*/  container_set_geometry_from_content (struct sway_container*) ; 
 void* fmax (void*,void*) ; 

void view_update_size(struct sway_view *view, int width, int height) {
	struct sway_container *con = view->container;

	if (container_is_floating(con)) {
		con->content_width = width;
		con->content_height = height;
		con->current.content_width = width;
		con->current.content_height = height;
		container_set_geometry_from_content(con);
	} else {
		con->surface_x = con->content_x + (con->content_width - width) / 2;
		con->surface_y = con->content_y + (con->content_height - height) / 2;
		con->surface_x = fmax(con->surface_x, con->content_x);
		con->surface_y = fmax(con->surface_y, con->content_y);
	}
	con->surface_width = width;
	con->surface_height = height;
}