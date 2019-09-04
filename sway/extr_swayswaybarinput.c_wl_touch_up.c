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
typedef  int uint32_t ;
struct wl_touch {int dummy; } ;
struct touch_slot {int time; int /*<<< orphan*/ * output; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct swaybar_seat {int /*<<< orphan*/  touch; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 struct touch_slot* get_touch_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_hotspots (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wl_touch_up(void *data, struct wl_touch *wl_touch,
		uint32_t serial, uint32_t time, int32_t id) {
	struct swaybar_seat *seat = data;
	struct touch_slot *slot = get_touch_slot(&seat->touch, id);
	if (!slot) {
		return;
	}
	if (time - slot->time < 500) {
		// Tap, treat it like a pointer click
		process_hotspots(slot->output, slot->x, slot->y, BTN_LEFT);
	}
	slot->output = NULL;
}