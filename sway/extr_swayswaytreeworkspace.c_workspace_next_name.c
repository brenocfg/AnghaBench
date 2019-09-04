#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct workspace_config {char* workspace; TYPE_5__* outputs; } ;
struct sway_output {TYPE_1__* wlr_output; } ;
struct sway_mode {TYPE_3__* keycode_bindings; TYPE_2__* keysym_bindings; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  identifier ;
struct TYPE_12__ {TYPE_4__* workspace_configs; struct sway_mode* current_mode; } ;
struct TYPE_11__ {int length; int /*<<< orphan*/ * items; } ;
struct TYPE_10__ {int length; struct workspace_config** items; } ;
struct TYPE_9__ {int length; int /*<<< orphan*/ * items; } ;
struct TYPE_8__ {int length; int /*<<< orphan*/ * items; } ;
struct TYPE_7__ {char* name; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 TYPE_6__* config ; 
 int /*<<< orphan*/  free (char*) ; 
 struct sway_output* output_by_name_or_id (char const*) ; 
 int /*<<< orphan*/  output_get_identifier (char*,int,struct sway_output*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ workspace_by_name (char*) ; 
 scalar_t__ workspace_by_number (char*) ; 
 int /*<<< orphan*/  workspace_name_from_binding (int /*<<< orphan*/ ,char const*,int*,char**) ; 

char *workspace_next_name(const char *output_name) {
	sway_log(SWAY_DEBUG, "Workspace: Generating new workspace name for output %s",
			output_name);
	// Scan for available workspace names by looking through output-workspace
	// assignments primarily, falling back to bindings and numbers.
	struct sway_mode *mode = config->current_mode;

	char identifier[128];
	struct sway_output *output = output_by_name_or_id(output_name);
	if (!output) {
		return NULL;
	}
	output_name = output->wlr_output->name;
	output_get_identifier(identifier, sizeof(identifier), output);

	int order = INT_MAX;
	char *target = NULL;
	for (int i = 0; i < mode->keysym_bindings->length; ++i) {
		workspace_name_from_binding(mode->keysym_bindings->items[i],
				output_name, &order, &target);
	}
	for (int i = 0; i < mode->keycode_bindings->length; ++i) {
		workspace_name_from_binding(mode->keycode_bindings->items[i],
				output_name, &order, &target);
	}
	for (int i = 0; i < config->workspace_configs->length; ++i) {
		// Unlike with bindings, this does not guarantee order
		const struct workspace_config *wsc = config->workspace_configs->items[i];
		if (workspace_by_name(wsc->workspace)) {
			continue;
		}
		bool found = false;
		for (int j = 0; j < wsc->outputs->length; ++j) {
			if (strcmp(wsc->outputs->items[j], "*") == 0 ||
					strcmp(wsc->outputs->items[j], output_name) == 0 ||
					strcmp(wsc->outputs->items[j], identifier) == 0) {
				found = true;
				free(target);
				target = strdup(wsc->workspace);
				break;
			}
		}
		if (found) {
			break;
		}
	}
	if (target != NULL) {
		return target;
	}
	// As a fall back, use the next available number
	char name[12] = "";
	unsigned int ws_num = 1;
	do {
		snprintf(name, sizeof(name), "%u", ws_num++);
	} while (workspace_by_number(name));
	return strdup(name);
}