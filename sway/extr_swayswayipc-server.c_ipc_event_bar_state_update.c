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
struct bar_config {int /*<<< orphan*/  visible_by_modifier; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_EVENT_BAR_STATE_UPDATE ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  ipc_has_event_listeners (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_send_event (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_new_boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object_new_object () ; 
 int /*<<< orphan*/  json_object_new_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_put (int /*<<< orphan*/ *) ; 
 char* json_object_to_json_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

void ipc_event_bar_state_update(struct bar_config *bar) {
	if (!ipc_has_event_listeners(IPC_EVENT_BAR_STATE_UPDATE)) {
		return;
	}
	sway_log(SWAY_DEBUG, "Sending bar_state_update event");

	json_object *json = json_object_new_object();
	json_object_object_add(json, "id", json_object_new_string(bar->id));
	json_object_object_add(json, "visible_by_modifier",
			json_object_new_boolean(bar->visible_by_modifier));

	const char *json_string = json_object_to_json_string(json);
	ipc_send_event(json_string, IPC_EVENT_BAR_STATE_UPDATE);
	json_object_put(json);
}