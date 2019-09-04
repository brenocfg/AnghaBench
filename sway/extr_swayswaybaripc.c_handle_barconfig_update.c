#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* left; void* bottom; void* right; void* top; } ;
struct swaybar_config {char* hidden_state; char* mode; TYPE_1__ gaps; } ;
struct swaybar {char* id; struct swaybar_config* config; } ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int determine_bar_visibility (struct swaybar*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* json_object_get_int (int /*<<< orphan*/ *) ; 
 char const* json_object_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_object_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  json_object_object_get_ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static bool handle_barconfig_update(struct swaybar *bar,
		json_object *json_config) {
	json_object *json_id;
	json_object_object_get_ex(json_config, "id", &json_id);
	const char *id = json_object_get_string(json_id);
	if (strcmp(id, bar->id) != 0) {
		return false;
	}

	struct swaybar_config *config = bar->config;

	json_object *json_state;
	json_object_object_get_ex(json_config, "hidden_state", &json_state);
	const char *new_state = json_object_get_string(json_state);
	char *old_state = config->hidden_state;
	if (strcmp(new_state, old_state) != 0) {
		sway_log(SWAY_DEBUG, "Changing bar hidden state to %s", new_state);
		free(old_state);
		config->hidden_state = strdup(new_state);
		return determine_bar_visibility(bar, false);
	}

	free(config->mode);
	json_object *json_mode;
	json_object_object_get_ex(json_config, "mode", &json_mode);
	config->mode = strdup(json_object_get_string(json_mode));
	sway_log(SWAY_DEBUG, "Changing bar mode to %s", config->mode);

	json_object *gaps;
	json_object_object_get_ex(json_config, "gaps", &gaps);
	if (gaps) {
		json_object *top = json_object_object_get(gaps, "top");
		if (top) {
			config->gaps.top = json_object_get_int(top);
		}
		json_object *right = json_object_object_get(gaps, "right");
		if (right) {
			config->gaps.right = json_object_get_int(right);
		}
		json_object *bottom = json_object_object_get(gaps, "bottom");
		if (bottom) {
			config->gaps.bottom = json_object_get_int(bottom);
		}
		json_object *left = json_object_object_get(gaps, "left");
		if (left) {
			config->gaps.left = json_object_get_int(left);
		}
	}

	return determine_bar_visibility(bar, true);
}