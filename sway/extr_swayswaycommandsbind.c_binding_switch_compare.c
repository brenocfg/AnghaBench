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
struct sway_switch_binding {scalar_t__ type; scalar_t__ state; } ;

/* Variables and functions */

__attribute__((used)) static bool binding_switch_compare(struct sway_switch_binding *binding_a,
		struct sway_switch_binding *binding_b) {
	if (binding_a->type != binding_b->type) {
		return false;
	}
	if (binding_a->state != binding_b->state) {
		return false;
	}
	return true;
}