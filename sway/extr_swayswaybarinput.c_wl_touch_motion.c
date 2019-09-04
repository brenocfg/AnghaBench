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
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_touch {int dummy; } ;
struct touch_slot {int x; int start_x; TYPE_1__* output; void* y; } ;
struct swaybar_seat {int /*<<< orphan*/  bar; int /*<<< orphan*/  touch; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int width; } ;

/* Variables and functions */
 int abs (int) ; 
 struct touch_slot* get_touch_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* wl_fixed_to_double (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workspace_next (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static void wl_touch_motion(void *data, struct wl_touch *wl_touch,
		uint32_t time, int32_t id, wl_fixed_t x, wl_fixed_t y) {
	struct swaybar_seat *seat = data;
	struct touch_slot *slot = get_touch_slot(&seat->touch, id);
	if (!slot) {
		return;
	}
	int prev_progress = (int)((slot->x - slot->start_x)
			/ slot->output->width * 100);
	slot->x = wl_fixed_to_double(x);
	slot->y = wl_fixed_to_double(y);
	// "progress" is a measure from 0..100 representing the fraction of the
	// output the touch gesture has travelled, positive when moving to the right
	// and negative when moving to the left.
	int progress = (int)((slot->x - slot->start_x)
			/ slot->output->width * 100);
	if (abs(progress) / 20 != abs(prev_progress) / 20) {
		workspace_next(seat->bar, slot->output, progress - prev_progress < 0);
	}
}