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
struct TYPE_4__ {int /*<<< orphan*/ * touch; } ;
struct TYPE_3__ {int /*<<< orphan*/ * cursor_surface; int /*<<< orphan*/ * pointer; } ;
struct swaybar_seat {int /*<<< orphan*/  link; int /*<<< orphan*/  wl_seat; TYPE_2__ touch; TYPE_1__ pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct swaybar_seat*) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_pointer_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_seat_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_touch_release (int /*<<< orphan*/ *) ; 

void swaybar_seat_free(struct swaybar_seat *seat) {
	if (!seat) {
		return;
	}
	if (seat->pointer.pointer != NULL) {
		wl_pointer_release(seat->pointer.pointer);
	}
	if (seat->pointer.cursor_surface != NULL) {
		wl_surface_destroy(seat->pointer.cursor_surface);
	}
	if (seat->touch.touch != NULL) {
		wl_touch_release(seat->touch.touch);
	}
	wl_seat_destroy(seat->wl_seat);
	wl_list_remove(&seat->link);
	free(seat);
}