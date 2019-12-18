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
struct input_config {char* identifier; int /*<<< orphan*/ * xkb_file; int /*<<< orphan*/  xkb_file_is_set; } ;
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
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  validate_type_on_existing (struct input_config*,char**) ; 
 int /*<<< orphan*/  validate_wildcard_on_all (struct input_config*,char**) ; 
 int /*<<< orphan*/  validate_xkb_merge (struct input_config*,struct input_config*,char**) ; 

struct input_config *store_input_config(struct input_config *ic,
		char **error) {
	bool wildcard = strcmp(ic->identifier, "*") == 0;
	if (wildcard && error && !validate_wildcard_on_all(ic, error)) {
		return NULL;
	}

	bool type = strncmp(ic->identifier, "type:", strlen("type:")) == 0;
	if (type && error && !validate_type_on_existing(ic, error)) {
		return NULL;
	}

	list_t *config_list = type ? config->input_type_configs
		: config->input_configs;

	struct input_config *current = NULL;
	bool new_current = false;

	int i = list_seq_find(config_list, input_identifier_cmp, ic->identifier);
	if (i >= 0) {
		current = config_list->items[i];
	}

	i = list_seq_find(config->input_configs, input_identifier_cmp, "*");
	if (!current && i >= 0) {
		current = new_input_config(ic->identifier);
		merge_input_config(current, config->input_configs->items[i]);
		new_current = true;
	}

	if (error && !validate_xkb_merge(current, ic, error)) {
		if (new_current) {
			free_input_config(current);
		}
		return NULL;
	}

	if (wildcard) {
		merge_wildcard_on_all(ic);
	}

	if (type) {
		merge_type_on_existing(ic);
	}

	if (current) {
		merge_input_config(current, ic);
		free_input_config(ic);
		ic = current;
	}

	ic->xkb_file_is_set = ic->xkb_file != NULL;

	if (!current || new_current) {
		list_add(config_list, ic);
	}

	sway_log(SWAY_DEBUG, "Config stored for input %s", ic->identifier);

	return ic;
}