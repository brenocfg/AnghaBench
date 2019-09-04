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
struct swaybar_tray {int /*<<< orphan*/  basedirs; int /*<<< orphan*/  themes; int /*<<< orphan*/  bus; int /*<<< orphan*/  watcher_kde; int /*<<< orphan*/  watcher_xdg; TYPE_1__* items; int /*<<< orphan*/  host_kde; int /*<<< orphan*/  host_xdg; } ;
struct TYPE_2__ {int length; int /*<<< orphan*/ * items; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_sni (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_watcher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_host (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_themes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct swaybar_tray*) ; 
 int /*<<< orphan*/  list_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_bus_flush_close_unref (int /*<<< orphan*/ ) ; 

void destroy_tray(struct swaybar_tray *tray) {
	if (!tray) {
		return;
	}
	finish_host(&tray->host_xdg);
	finish_host(&tray->host_kde);
	for (int i = 0; i < tray->items->length; ++i) {
		destroy_sni(tray->items->items[i]);
	}
	list_free(tray->items);
	destroy_watcher(tray->watcher_xdg);
	destroy_watcher(tray->watcher_kde);
	sd_bus_flush_close_unref(tray->bus);
	finish_themes(tray->themes, tray->basedirs);
	free(tray);
}