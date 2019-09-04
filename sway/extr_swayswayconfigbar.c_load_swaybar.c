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
struct bar_config {scalar_t__ pid; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  invoke_swaybar (struct bar_config*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  terminate_swaybar (scalar_t__) ; 

void load_swaybar(struct bar_config *bar) {
	if (bar->pid != 0) {
		terminate_swaybar(bar->pid);
	}
	sway_log(SWAY_DEBUG, "Invoking swaybar for bar id '%s'", bar->id);
	invoke_swaybar(bar);
}