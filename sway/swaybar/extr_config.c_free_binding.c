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
struct swaybar_binding {struct swaybar_binding* command; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct swaybar_binding*) ; 

void free_binding(struct swaybar_binding *binding) {
	if (!binding) {
		return;
	}
	free(binding->command);
	free(binding);
}