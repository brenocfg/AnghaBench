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
struct sway_tablet {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_tablet*) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

void sway_tablet_destroy(struct sway_tablet *tablet) {
	if (!tablet) {
		return;
	}
	wl_list_remove(&tablet->link);
	free(tablet);
}