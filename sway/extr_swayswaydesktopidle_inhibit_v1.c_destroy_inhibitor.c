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
struct TYPE_2__ {int /*<<< orphan*/  link; } ;
struct sway_idle_inhibitor_v1 {int /*<<< orphan*/  manager; TYPE_1__ destroy; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_idle_inhibitor_v1*) ; 
 int /*<<< orphan*/  sway_idle_inhibit_v1_check_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_inhibitor(struct sway_idle_inhibitor_v1 *inhibitor) {
	wl_list_remove(&inhibitor->link);
	wl_list_remove(&inhibitor->destroy.link);
	sway_idle_inhibit_v1_check_active(inhibitor->manager);
	free(inhibitor);
}