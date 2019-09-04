#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sway_cursor {int hidden; char* image; int /*<<< orphan*/  image_client; int /*<<< orphan*/  hotspot_y; int /*<<< orphan*/  hotspot_x; scalar_t__ image_surface; } ;

/* Variables and functions */
 int /*<<< orphan*/  cursor_rebase (struct sway_cursor*) ; 
 int /*<<< orphan*/  cursor_set_image (struct sway_cursor*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursor_set_image_surface (struct sway_cursor*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cursor_unhide(struct sway_cursor *cursor) {
	cursor->hidden = false;
	if (cursor->image_surface) {
		cursor_set_image_surface(cursor,
				cursor->image_surface,
				cursor->hotspot_x,
				cursor->hotspot_y,
				cursor->image_client);
	} else {
		const char *image = cursor->image;
		cursor->image = NULL;
		cursor_set_image(cursor, image, cursor->image_client);
	}
	cursor_rebase(cursor);
}