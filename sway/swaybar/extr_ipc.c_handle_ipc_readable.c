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
struct swaybar {int /*<<< orphan*/  mode_pango_markup; int /*<<< orphan*/ * mode; int /*<<< orphan*/  visible_by_mode; int /*<<< orphan*/  ipc_event_socketfd; } ;
struct ipc_response {int type; int /*<<< orphan*/  payload; } ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
#define  IPC_EVENT_BARCONFIG_UPDATE 131 
#define  IPC_EVENT_BAR_STATE_UPDATE 130 
#define  IPC_EVENT_MODE 129 
#define  IPC_EVENT_WORKSPACE 128 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  determine_bar_visibility (struct swaybar*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_ipc_response (struct ipc_response*) ; 
 int handle_bar_state_update (struct swaybar*,int /*<<< orphan*/ *) ; 
 int handle_barconfig_update (struct swaybar*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ipc_get_workspaces (struct swaybar*) ; 
 struct ipc_response* ipc_recv_response (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_object_get_boolean (int /*<<< orphan*/ *) ; 
 char* json_object_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_object_get_ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  json_object_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_tokener_parse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

bool handle_ipc_readable(struct swaybar *bar) {
	struct ipc_response *resp = ipc_recv_response(bar->ipc_event_socketfd);
	if (!resp) {
		return false;
	}

	json_object *result = json_tokener_parse(resp->payload);
	if (!result) {
		sway_log(SWAY_ERROR, "failed to parse payload as json");
		free_ipc_response(resp);
		return false;
	}

	bool bar_is_dirty = true;
	switch (resp->type) {
	case IPC_EVENT_WORKSPACE:
		bar_is_dirty = ipc_get_workspaces(bar);
		break;
	case IPC_EVENT_MODE: {
		json_object *json_change, *json_pango_markup;
		if (json_object_object_get_ex(result, "change", &json_change)) {
			const char *change = json_object_get_string(json_change);
			free(bar->mode);
			bar->mode = strcmp(change, "default") != 0 ? strdup(change) : NULL;
			bar->visible_by_mode = bar->mode != NULL;
			determine_bar_visibility(bar, false);
		} else {
			sway_log(SWAY_ERROR, "failed to parse response");
			bar_is_dirty = false;
			break;
		}
		if (json_object_object_get_ex(result,
					"pango_markup", &json_pango_markup)) {
			bar->mode_pango_markup = json_object_get_boolean(json_pango_markup);
		}
		break;
	}
	case IPC_EVENT_BARCONFIG_UPDATE:
		bar_is_dirty = handle_barconfig_update(bar, resp->payload, result);
		break;
	case IPC_EVENT_BAR_STATE_UPDATE:
		bar_is_dirty = handle_bar_state_update(bar, result);
		break;
	default:
		bar_is_dirty = false;
		break;
	}
	json_object_put(result);
	free_ipc_response(resp);
	return bar_is_dirty;
}