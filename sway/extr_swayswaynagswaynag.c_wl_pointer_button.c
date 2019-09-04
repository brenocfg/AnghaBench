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
typedef  scalar_t__ uint32_t ;
struct wl_pointer {int dummy; } ;
struct swaynag_button {double x; double y; double width; double height; } ;
struct TYPE_6__ {int total_lines; int visible_lines; int offset; struct swaynag_button button_down; struct swaynag_button button_up; scalar_t__ visible; } ;
struct TYPE_4__ {double x; double y; } ;
struct swaynag {double scale; TYPE_3__ details; TYPE_2__* buttons; TYPE_1__ pointer; } ;
struct TYPE_5__ {int length; struct swaynag_button** items; } ;

/* Variables and functions */
 scalar_t__ WL_POINTER_BUTTON_STATE_PRESSED ; 
 int /*<<< orphan*/  render_frame (struct swaynag*) ; 
 int /*<<< orphan*/  swaynag_button_execute (struct swaynag*,struct swaynag_button*) ; 

__attribute__((used)) static void wl_pointer_button(void *data, struct wl_pointer *wl_pointer,
		uint32_t serial, uint32_t time, uint32_t button, uint32_t state) {
	struct swaynag *swaynag = data;

	if (state != WL_POINTER_BUTTON_STATE_PRESSED) {
		return;
	}

	double x = swaynag->pointer.x * swaynag->scale;
	double y = swaynag->pointer.y * swaynag->scale;
	for (int i = 0; i < swaynag->buttons->length; i++) {
		struct swaynag_button *nagbutton = swaynag->buttons->items[i];
		if (x >= nagbutton->x
				&& y >= nagbutton->y
				&& x < nagbutton->x + nagbutton->width
				&& y < nagbutton->y + nagbutton->height) {
			swaynag_button_execute(swaynag, nagbutton);
			return;
		}
	}

	if (swaynag->details.visible &&
			swaynag->details.total_lines != swaynag->details.visible_lines) {
		struct swaynag_button button_up = swaynag->details.button_up;
		if (x >= button_up.x
				&& y >= button_up.y
				&& x < button_up.x + button_up.width
				&& y < button_up.y + button_up.height
				&& swaynag->details.offset > 0) {
			swaynag->details.offset--;
			render_frame(swaynag);
			return;
		}

		struct swaynag_button button_down = swaynag->details.button_down;
		int bot = swaynag->details.total_lines;
		bot -= swaynag->details.visible_lines;
		if (x >= button_down.x
				&& y >= button_down.y
				&& x < button_down.x + button_down.width
				&& y < button_down.y + button_down.height
				&& swaynag->details.offset < bot) {
			swaynag->details.offset++;
			render_frame(swaynag);
			return;
		}
	}
}