#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct input_config {char* identifier; } ;
struct TYPE_5__ {struct input_config** items; } ;
typedef  TYPE_1__ list_t ;
struct TYPE_6__ {TYPE_1__* input_configs; TYPE_1__* input_type_configs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 TYPE_4__* config ; 
 int /*<<< orphan*/  free_input_config (struct input_config*) ; 
 int /*<<< orphan*/  input_identifier_cmp ; 
 int /*<<< orphan*/  list_add (TYPE_1__*,struct input_config*) ; 
 int list_seq_find (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  merge_input_config (struct input_config*,struct input_config*) ; 
 int /*<<< orphan*/  merge_type_on_existing (struct input_config*) ; 
 int /*<<< orphan*/  merge_wildcard_on_all (struct input_config*) ; 
 struct input_config* new_input_config (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 

struct input_config *store_input_config(struct input_config *ic) {
	bool wildcard = strcmp(ic->identifier, "*") == 0;
	if (wildcard) {
		merge_wildcard_on_all(ic);
	}

	list_t *config_list = NULL;
	if (strncmp(ic->identifier, "type:", 5) == 0) {
		config_list = config->input_type_configs;
		merge_type_on_existing(ic);
	} else {
		config_list = config->input_configs;
	}

	int i = list_seq_find(config_list, input_identifier_cmp,
			ic->identifier);
	if (i >= 0) {
		sway_log(SWAY_DEBUG, "Merging on top of existing input config");
		struct input_config *current = config_list->items[i];
		merge_input_config(current, ic);
		free_input_config(ic);
		ic = current;
	} else if (!wildcard) {
		sway_log(SWAY_DEBUG, "Adding non-wildcard input config");
		i = list_seq_find(config->input_configs, input_identifier_cmp, "*");
		if (i >= 0) {
			sway_log(SWAY_DEBUG, "Merging on top of input * config");
			struct input_config *current = new_input_config(ic->identifier);
			merge_input_config(current, config->input_configs->items[i]);
			merge_input_config(current, ic);
			free_input_config(ic);
			ic = current;
		}
		list_add(config_list, ic);
	} else {
		// New wildcard config. Just add it
		sway_log(SWAY_DEBUG, "Adding input * config");
		list_add(config->input_configs, ic);
	}

	sway_log(SWAY_DEBUG, "Config stored for input %s", ic->identifier);

	return ic;
}