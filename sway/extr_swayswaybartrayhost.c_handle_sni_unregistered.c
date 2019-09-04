#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct swaybar_tray {int /*<<< orphan*/  bar; TYPE_1__* items; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
struct TYPE_3__ {int /*<<< orphan*/ * items; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  SWAY_INFO ; 
 int /*<<< orphan*/  cmp_sni_id ; 
 int /*<<< orphan*/  destroy_sni (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (TYPE_1__*,int) ; 
 int list_seq_find (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  set_bar_dirty (int /*<<< orphan*/ ) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int handle_sni_unregistered(sd_bus_message *msg, void *data,
		sd_bus_error *error) {
	char *id;
	int ret = sd_bus_message_read(msg, "s", &id);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to parse unregister SNI message: %s", strerror(-ret));
	}

	struct swaybar_tray *tray = data;
	int idx = list_seq_find(tray->items, cmp_sni_id, id);
	if (idx != -1) {
		sway_log(SWAY_INFO, "Unregistering Status Notifier Item '%s'", id);
		destroy_sni(tray->items->items[idx]);
		list_del(tray->items, idx);
		set_bar_dirty(tray->bar);
	}
	return ret;
}