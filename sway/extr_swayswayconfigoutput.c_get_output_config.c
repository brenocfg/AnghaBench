#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sway_output {TYPE_3__* wlr_output; } ;
struct output_config {char* name; int /*<<< orphan*/  dpms_state; int /*<<< orphan*/  background_option; int /*<<< orphan*/  background; int /*<<< orphan*/  transform; int /*<<< orphan*/  scale; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  refresh_rate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  enabled; } ;
struct TYPE_7__ {scalar_t__ reloading; TYPE_1__* output_configs; } ;
struct TYPE_6__ {char* name; } ;
struct TYPE_5__ {struct output_config** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 TYPE_4__* config ; 
 int /*<<< orphan*/  default_output_config (struct output_config*,TYPE_3__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_output_config (struct output_config*) ; 
 int /*<<< orphan*/  list_add (TYPE_1__*,struct output_config*) ; 
 int list_seq_find (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  merge_output_config (struct output_config*,struct output_config*) ; 
 struct output_config* new_output_config (char*) ; 
 int /*<<< orphan*/  output_name_cmp ; 
 int snprintf (char*,size_t,char*,char*,char const*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct output_config *get_output_config(char *identifier,
		struct sway_output *sway_output) {
	const char *name = sway_output->wlr_output->name;

	struct output_config *oc_id_on_name = NULL;
	struct output_config *oc_name = NULL;
	struct output_config *oc_id = NULL;

	size_t length = snprintf(NULL, 0, "%s on %s", identifier, name) + 1;
	char *id_on_name = malloc(length);
	snprintf(id_on_name, length, "%s on %s", identifier, name);
	int i = list_seq_find(config->output_configs, output_name_cmp, id_on_name);
	if (i >= 0) {
		oc_id_on_name = config->output_configs->items[i];
	} else {
		i = list_seq_find(config->output_configs, output_name_cmp, name);
		if (i >= 0) {
			oc_name = config->output_configs->items[i];
		}

		i = list_seq_find(config->output_configs, output_name_cmp, identifier);
		if (i >= 0) {
			oc_id = config->output_configs->items[i];
		}
	}

	struct output_config *result = new_output_config("temp");
	if (config->reloading) {
		default_output_config(result, sway_output->wlr_output);
	}
	if (oc_id_on_name) {
		// Already have an identifier on name config, use that
		free(result->name);
		result->name = strdup(id_on_name);
		merge_output_config(result, oc_id_on_name);
	} else if (oc_name && oc_id) {
		// Generate a config named `<identifier> on <name>` which contains a
		// merged copy of the identifier on name. This will make sure that both
		// identifier and name configs are respected, with identifier getting
		// priority
		struct output_config *temp = new_output_config(id_on_name);
		merge_output_config(temp, oc_name);
		merge_output_config(temp, oc_id);
		list_add(config->output_configs, temp);

		free(result->name);
		result->name = strdup(id_on_name);
		merge_output_config(result, temp);

		sway_log(SWAY_DEBUG, "Generated output config \"%s\" (enabled: %d)"
			" (%dx%d@%fHz position %d,%d scale %f transform %d) (bg %s %s)"
			" (dpms %d)", result->name, result->enabled, result->width,
			result->height, result->refresh_rate, result->x, result->y,
			result->scale, result->transform, result->background,
			result->background_option, result->dpms_state);
	} else if (oc_name) {
		// No identifier config, just return a copy of the name config
		free(result->name);
		result->name = strdup(name);
		merge_output_config(result, oc_name);
	} else if (oc_id) {
		// No name config, just return a copy of the identifier config
		free(result->name);
		result->name = strdup(identifier);
		merge_output_config(result, oc_id);
	} else {
		i = list_seq_find(config->output_configs, output_name_cmp, "*");
		if (i >= 0) {
			// No name or identifier config, but there is a wildcard config
			free(result->name);
			result->name = strdup("*");
			merge_output_config(result, config->output_configs->items[i]);
		} else if (!config->reloading) {
			// No name, identifier, or wildcard config. Since we are not
			// reloading with defaults, the output config will be empty, so
			// just return NULL
			free_output_config(result);
			result = NULL;
		}
	}

	free(id_on_name);
	return result;
}