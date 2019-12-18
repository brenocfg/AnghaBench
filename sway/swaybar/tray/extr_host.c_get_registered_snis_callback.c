#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct swaybar_tray {int dummy; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
struct TYPE_5__ {int /*<<< orphan*/  message; } ;
typedef  TYPE_1__ sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  add_sni (struct swaybar_tray*,char*) ; 
 int sd_bus_error_get_errno (TYPE_1__*) ; 
 int sd_bus_message_enter_container (int /*<<< orphan*/ *,char,int /*<<< orphan*/ *) ; 
 TYPE_1__* sd_bus_message_get_error (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_bus_message_is_method_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_bus_message_read_strv (int /*<<< orphan*/ *,char***) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_registered_snis_callback(sd_bus_message *msg, void *data,
		sd_bus_error *error) {
	if (sd_bus_message_is_method_error(msg, NULL)) {
		sd_bus_error err = *sd_bus_message_get_error(msg);
		sway_log(SWAY_ERROR, "Failed to get registered SNIs: %s", err.message);
		return -sd_bus_error_get_errno(&err);
	}

	int ret = sd_bus_message_enter_container(msg, 'v', NULL);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to read registered SNIs: %s", strerror(-ret));
		return ret;
	}

	char **ids;
	ret = sd_bus_message_read_strv(msg, &ids);
	if (ret < 0) {
		sway_log(SWAY_ERROR, "Failed to read registered SNIs: %s", strerror(-ret));
		return ret;
	}

	if (ids) {
		struct swaybar_tray *tray = data;
		for (char **id = ids; *id; ++id) {
			add_sni(tray, *id);
		}
	}

	return ret;
}