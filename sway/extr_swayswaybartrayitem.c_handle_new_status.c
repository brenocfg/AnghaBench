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
struct swaybar_sni {int /*<<< orphan*/  status; int /*<<< orphan*/  watcher_id; } ;
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int sd_bus_message_read (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  set_sni_dirty (struct swaybar_sni*) ; 
 int sni_check_msg_sender (struct swaybar_sni*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sni_get_property_async (struct swaybar_sni*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int handle_new_status(sd_bus_message *msg, void *data, sd_bus_error *error) {
	struct swaybar_sni *sni = data;
	int ret = sni_check_msg_sender(sni, msg, "status");
	if (ret == 1) {
		char *status;
		int r = sd_bus_message_read(msg, "s", &status);
		if (r < 0) {
			sway_log(SWAY_ERROR, "%s new status error: %s", sni->watcher_id, strerror(-ret));
			ret = r;
		} else {
			free(sni->status);
			sni->status = strdup(status);
			sway_log(SWAY_DEBUG, "%s has new status = '%s'", sni->watcher_id, status);
			set_sni_dirty(sni);
		}
	} else {
		sni_get_property_async(sni, "Status", "s", &sni->status);
	}

	return ret;
}