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
struct sway_switch_binding {struct sway_switch_binding* command; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_switch_binding*) ; 

void free_switch_binding(struct sway_switch_binding *binding) {
	if (!binding) {
		return;
	}
	free(binding->command);
	free(binding);
}