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
struct swaybar {int visible_by_mode; int visible_by_urgency; int /*<<< orphan*/  visible_by_modifier; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 int determine_bar_visibility (struct swaybar*,int) ; 
 int /*<<< orphan*/  json_object_get_boolean (int /*<<< orphan*/ *) ; 
 char* json_object_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_object_get_ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool handle_bar_state_update(struct swaybar *bar, json_object *event) {
	json_object *json_id;
	json_object_object_get_ex(event, "id", &json_id);
	const char *id = json_object_get_string(json_id);
	if (strcmp(id, bar->id) != 0) {
		return false;
	}

	json_object *visible_by_modifier;
	json_object_object_get_ex(event, "visible_by_modifier", &visible_by_modifier);
	bar->visible_by_modifier = json_object_get_boolean(visible_by_modifier);
	if (bar->visible_by_modifier) {
		// If the bar is visible by modifier, clear both visible by mode and
		// urgency as modifier has precedence and the bar should be hidden
		// again when it is no longer visible by modifier.
		bar->visible_by_mode = false;
		bar->visible_by_urgency = false;
	}
	return determine_bar_visibility(bar, false);
}