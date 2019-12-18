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
typedef  scalar_t__ uint32_t ;
struct swaybar_binding {scalar_t__ button; int release; } ;
struct swaybar {TYPE_2__* config; } ;
struct TYPE_4__ {TYPE_1__* bindings; } ;
struct TYPE_3__ {int length; struct swaybar_binding** items; } ;

/* Variables and functions */
 scalar_t__ WL_POINTER_BUTTON_STATE_RELEASED ; 
 int /*<<< orphan*/  ipc_execute_binding (struct swaybar*,struct swaybar_binding*) ; 

__attribute__((used)) static bool check_bindings(struct swaybar *bar, uint32_t button,
		uint32_t state) {
	bool released = state == WL_POINTER_BUTTON_STATE_RELEASED;
	for (int i = 0; i < bar->config->bindings->length; i++) {
		struct swaybar_binding *binding = bar->config->bindings->items[i];
		if (binding->button == button && binding->release == released) {
			ipc_execute_binding(bar, binding);
			return true;
		}
	}
	return false;
}