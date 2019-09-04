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
struct swaybar_tray {int /*<<< orphan*/  basedirs; int /*<<< orphan*/  themes; int /*<<< orphan*/  host_kde; int /*<<< orphan*/  host_xdg; int /*<<< orphan*/  items; int /*<<< orphan*/ * bus; void* watcher_kde; void* watcher_xdg; int /*<<< orphan*/  fd; struct swaybar* bar; } ;
struct swaybar {int dummy; } ;
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 struct swaybar_tray* calloc (int,int) ; 
 int /*<<< orphan*/  create_list () ; 
 void* create_watcher (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_lost_watcher ; 
 int /*<<< orphan*/  init_host (int /*<<< orphan*/ *,char*,struct swaybar_tray*) ; 
 int /*<<< orphan*/  init_themes (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_bus_get_fd (int /*<<< orphan*/ *) ; 
 int sd_bus_match_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,struct swaybar_tray*) ; 
 int sd_bus_open_user (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 

struct swaybar_tray *create_tray(struct swaybar *bar) {
	sway_log(SWAY_DEBUG, "Initializing tray");

	sd_bus *bus;
	int ret = sd_bus_open_user(&bus);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to connect to user bus: %s", strerror(-ret));
		return NULL;
	}

	struct swaybar_tray *tray = calloc(1, sizeof(struct swaybar_tray));
	if (!tray) {
		return NULL;
	}
	tray->bar = bar;
	tray->bus = bus;
	tray->fd = sd_bus_get_fd(tray->bus);

	tray->watcher_xdg = create_watcher("freedesktop", tray->bus);
	tray->watcher_kde = create_watcher("kde", tray->bus);

	ret = sd_bus_match_signal(bus, NULL, "org.freedesktop.DBus",
			"/org/freedesktop/DBus", "org.freedesktop.DBus",
			"NameOwnerChanged", handle_lost_watcher, tray);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to subscribe to unregistering events: %s",
				strerror(-ret));
	}

	tray->items = create_list();

	init_host(&tray->host_xdg, "freedesktop", tray);
	init_host(&tray->host_kde, "kde", tray);

	init_themes(&tray->themes, &tray->basedirs);

	return tray;
}