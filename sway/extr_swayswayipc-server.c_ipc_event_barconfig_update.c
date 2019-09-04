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
struct bar_config {int dummy; } ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_EVENT_BARCONFIG_UPDATE ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  ipc_has_event_listeners (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ipc_json_describe_bar_config (struct bar_config*) ; 
 int /*<<< orphan*/  ipc_send_event (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_put (int /*<<< orphan*/ *) ; 
 char* json_object_to_json_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

void ipc_event_barconfig_update(struct bar_config *bar) {
	if (!ipc_has_event_listeners(IPC_EVENT_BARCONFIG_UPDATE)) {
		return;
	}
	sway_log(SWAY_DEBUG, "Sending barconfig_update event");
	json_object *json = ipc_json_describe_bar_config(bar);

	const char *json_string = json_object_to_json_string(json);
	ipc_send_event(json_string, IPC_EVENT_BARCONFIG_UPDATE);
	json_object_put(json);
}