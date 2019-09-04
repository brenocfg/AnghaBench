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
struct wlr_surface {int dummy; } ;
struct wl_client {int dummy; } ;
struct sway_cursor {int /*<<< orphan*/  cursor; scalar_t__ hidden; struct wl_client* image_client; void* hotspot_y; void* hotspot_x; struct wlr_surface* image_surface; int /*<<< orphan*/ * image; TYPE_2__* seat; } ;
typedef  void* int32_t ;
struct TYPE_4__ {TYPE_1__* wlr_seat; } ;
struct TYPE_3__ {int capabilities; } ;

/* Variables and functions */
 int WL_SEAT_CAPABILITY_POINTER ; 
 int /*<<< orphan*/  wlr_cursor_set_surface (int /*<<< orphan*/ ,struct wlr_surface*,void*,void*) ; 

void cursor_set_image_surface(struct sway_cursor *cursor,
		struct wlr_surface *surface, int32_t hotspot_x, int32_t hotspot_y,
		struct wl_client *client) {
	if (!(cursor->seat->wlr_seat->capabilities & WL_SEAT_CAPABILITY_POINTER)) {
		return;
	}

	cursor->image = NULL;
	cursor->image_surface = surface;
	cursor->hotspot_x = hotspot_x;
	cursor->hotspot_y = hotspot_y;
	cursor->image_client = client;

	if (cursor->hidden) {
		return;
	}

	wlr_cursor_set_surface(cursor->cursor, surface, hotspot_x, hotspot_y);
}