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
struct sway_idle_inhibitor_v1 {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ INHIBIT_IDLE_APPLICATION ; 
 int /*<<< orphan*/  destroy_inhibitor (struct sway_idle_inhibitor_v1*) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 

void sway_idle_inhibit_v1_user_inhibitor_destroy(
		struct sway_idle_inhibitor_v1 *inhibitor) {
	if (!inhibitor) {
		return;
	}
	if (!sway_assert(inhibitor->mode != INHIBIT_IDLE_APPLICATION,
				"User should not be able to destroy application inhibitor")) {
		return;
	}
	destroy_inhibitor(inhibitor);
}