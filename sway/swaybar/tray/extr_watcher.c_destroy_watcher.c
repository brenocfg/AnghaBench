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
struct swaybar_watcher {struct swaybar_watcher* interface; int /*<<< orphan*/  items; int /*<<< orphan*/  hosts; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct swaybar_watcher*) ; 
 int /*<<< orphan*/  list_free_items_and_destroy (int /*<<< orphan*/ ) ; 

void destroy_watcher(struct swaybar_watcher *watcher) {
	if (!watcher) {
		return;
	}
	list_free_items_and_destroy(watcher->hosts);
	list_free_items_and_destroy(watcher->items);
	free(watcher->interface);
	free(watcher);
}