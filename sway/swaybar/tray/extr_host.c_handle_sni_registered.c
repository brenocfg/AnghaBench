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
struct swaybar_tray {int dummy; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  add_sni (struct swaybar_tray*,char*) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_sni_registered(sd_bus_message *msg, void *data,
		sd_bus_error *error) {
	char *id;
	int ret = sd_bus_message_read(msg, "s", &id);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to parse register SNI message: %s", strerror(-ret));
	}

	struct swaybar_tray *tray = data;
	add_sni(tray, id);

	return ret;
}