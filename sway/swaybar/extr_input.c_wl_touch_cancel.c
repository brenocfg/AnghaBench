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
struct wl_touch {int dummy; } ;
struct swaybar_touch {TYPE_1__* slots; } ;
struct swaybar_seat {struct swaybar_touch touch; } ;
struct TYPE_2__ {int /*<<< orphan*/ * output; } ;

/* Variables and functions */

__attribute__((used)) static void wl_touch_cancel(void *data, struct wl_touch *wl_touch) {
	struct swaybar_seat *seat = data;
	struct swaybar_touch *touch = &seat->touch;
	for (size_t i = 0; i < sizeof(touch->slots) / sizeof(*touch->slots); ++i) {
		touch->slots[i].output = NULL;
	}
}