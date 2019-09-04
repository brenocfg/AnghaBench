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
struct sway_container {int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_EVENT_WINDOW ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  ipc_has_event_listeners (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_json_describe_node_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_send_event (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object_new_object () ; 
 int /*<<< orphan*/  json_object_new_string (char const*) ; 
 int /*<<< orphan*/  json_object_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_put (int /*<<< orphan*/ *) ; 
 char* json_object_to_json_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*) ; 

void ipc_event_window(struct sway_container *window, const char *change) {
	if (!ipc_has_event_listeners(IPC_EVENT_WINDOW)) {
		return;
	}
	sway_log(SWAY_DEBUG, "Sending window::%s event", change);
	json_object *obj = json_object_new_object();
	json_object_object_add(obj, "change", json_object_new_string(change));
	json_object_object_add(obj, "container",
			ipc_json_describe_node_recursive(&window->node));

	const char *json_string = json_object_to_json_string(obj);
	ipc_send_event(json_string, IPC_EVENT_WINDOW);
	json_object_put(obj);
}