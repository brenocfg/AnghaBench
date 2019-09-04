#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct output_config {char* name; int /*<<< orphan*/  dpms_state; int /*<<< orphan*/  background_option; int /*<<< orphan*/  background; int /*<<< orphan*/  transform; int /*<<< orphan*/  subpixel; int /*<<< orphan*/  scale; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  refresh_rate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  enabled; } ;
struct TYPE_5__ {TYPE_1__* output_configs; } ;
struct TYPE_4__ {struct output_config** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 TYPE_3__* config ; 
 int /*<<< orphan*/  free_output_config (struct output_config*) ; 
 int /*<<< orphan*/  list_add (TYPE_1__*,struct output_config*) ; 
 int list_seq_find (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  merge_id_on_name (struct output_config*) ; 
 int /*<<< orphan*/  merge_output_config (struct output_config*,struct output_config*) ; 
 int /*<<< orphan*/  merge_wildcard_on_all (struct output_config*) ; 
 struct output_config* new_output_config (char*) ; 
 int /*<<< orphan*/  output_name_cmp ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sway_wl_output_subpixel_to_string (int /*<<< orphan*/ ) ; 

struct output_config *store_output_config(struct output_config *oc) {
	bool wildcard = strcmp(oc->name, "*") == 0;
	if (wildcard) {
		merge_wildcard_on_all(oc);
	} else {
		merge_id_on_name(oc);
	}

	int i = list_seq_find(config->output_configs, output_name_cmp, oc->name);
	if (i >= 0) {
		sway_log(SWAY_DEBUG, "Merging on top of existing output config");
		struct output_config *current = config->output_configs->items[i];
		merge_output_config(current, oc);
		free_output_config(oc);
		oc = current;
	} else if (!wildcard) {
		sway_log(SWAY_DEBUG, "Adding non-wildcard output config");
		i = list_seq_find(config->output_configs, output_name_cmp, "*");
		if (i >= 0) {
			sway_log(SWAY_DEBUG, "Merging on top of output * config");
			struct output_config *current = new_output_config(oc->name);
			merge_output_config(current, config->output_configs->items[i]);
			merge_output_config(current, oc);
			free_output_config(oc);
			oc = current;
		}
		list_add(config->output_configs, oc);
	} else {
		// New wildcard config. Just add it
		sway_log(SWAY_DEBUG, "Adding output * config");
		list_add(config->output_configs, oc);
	}

	sway_log(SWAY_DEBUG, "Config stored for output %s (enabled: %d) (%dx%d@%fHz "
		"position %d,%d scale %f subpixel %s transform %d) (bg %s %s) (dpms %d)",
		oc->name, oc->enabled, oc->width, oc->height, oc->refresh_rate,
		oc->x, oc->y, oc->scale, sway_wl_output_subpixel_to_string(oc->subpixel),
		oc->transform, oc->background, oc->background_option, oc->dpms_state);

	return oc;
}