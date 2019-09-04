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
struct sway_workspace {int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_EVENT_WORKSPACE ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  ipc_has_event_listeners (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ipc_json_describe_node_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_send_event (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object_new_object () ; 
 int /*<<< orphan*/ * json_object_new_string (char const*) ; 
 int /*<<< orphan*/  json_object_object_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_put (int /*<<< orphan*/ *) ; 
 char* json_object_to_json_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*) ; 

void ipc_event_workspace(struct sway_workspace *old,
		struct sway_workspace *new, const char *change) {
	if (!ipc_has_event_listeners(IPC_EVENT_WORKSPACE)) {
		return;
	}
	sway_log(SWAY_DEBUG, "Sending workspace::%s event", change);
	json_object *obj = json_object_new_object();
	json_object_object_add(obj, "change", json_object_new_string(change));
	if (old) {
		json_object_object_add(obj, "old",
				ipc_json_describe_node_recursive(&old->node));
	} else {
		json_object_object_add(obj, "old", NULL);
	}

	if (new) {
		json_object_object_add(obj, "current",
				ipc_json_describe_node_recursive(&new->node));
	} else {
		json_object_object_add(obj, "current", NULL);
	}

	const char *json_string = json_object_to_json_string(obj);
	ipc_send_event(json_string, IPC_EVENT_WORKSPACE);
	json_object_put(obj);
}