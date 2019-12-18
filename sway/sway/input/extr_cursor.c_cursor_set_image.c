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
struct wl_client {int dummy; } ;
struct sway_cursor {char* image; int /*<<< orphan*/  cursor; int /*<<< orphan*/  xcursor_manager; scalar_t__ hidden; struct wl_client* image_client; scalar_t__ hotspot_y; scalar_t__ hotspot_x; int /*<<< orphan*/ * image_surface; TYPE_2__* seat; } ;
struct TYPE_4__ {TYPE_1__* wlr_seat; } ;
struct TYPE_3__ {int capabilities; } ;

/* Variables and functions */
 int WL_SEAT_CAPABILITY_POINTER ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  wlr_cursor_set_image (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_xcursor_manager_set_cursor_image (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void cursor_set_image(struct sway_cursor *cursor, const char *image,
		struct wl_client *client) {
	if (!(cursor->seat->wlr_seat->capabilities & WL_SEAT_CAPABILITY_POINTER)) {
		return;
	}

	const char *current_image = cursor->image;
	cursor->image = image;
	cursor->image_surface = NULL;
	cursor->hotspot_x = cursor->hotspot_y = 0;
	cursor->image_client = client;

	if (cursor->hidden) {
		return;
	}

	if (!image) {
		wlr_cursor_set_image(cursor->cursor, NULL, 0, 0, 0, 0, 0, 0);
	} else if (!current_image || strcmp(current_image, image) != 0) {
		wlr_xcursor_manager_set_cursor_image(cursor->xcursor_manager, image,
				cursor->cursor);
	}
}