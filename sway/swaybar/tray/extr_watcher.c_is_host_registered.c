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
struct swaybar_watcher {TYPE_1__* hosts; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;
struct TYPE_2__ {scalar_t__ length; } ;

/* Variables and functions */
 int sd_bus_message_append_basic (int /*<<< orphan*/ *,char,int*) ; 

__attribute__((used)) static int is_host_registered(sd_bus *bus, const char *obj_path,
		const char *interface, const char *property, sd_bus_message *reply,
		void *data, sd_bus_error *error) {
	struct swaybar_watcher *watcher = data;
	int val = watcher->hosts->length > 0; // dbus expects int rather than bool
	return sd_bus_message_append_basic(reply, 'b', &val);
}