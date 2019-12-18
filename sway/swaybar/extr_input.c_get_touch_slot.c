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
struct touch_slot {scalar_t__ id; int /*<<< orphan*/  output; } ;
struct swaybar_touch {struct touch_slot* slots; } ;
typedef  int ssize_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct touch_slot *get_touch_slot(struct swaybar_touch *touch, int32_t id) {
	ssize_t next = -1;
	for (size_t i = 0; i < sizeof(touch->slots) / sizeof(*touch->slots); ++i) {
		if (touch->slots[i].id == id) {
			return &touch->slots[i];
		}
		if (next == -1 && !touch->slots[i].output) {
			next = i;
		}
	}
	if (next == -1) {
		sway_log(SWAY_ERROR, "Ran out of touch slots");
		return NULL;
	}
	return &touch->slots[next];
}