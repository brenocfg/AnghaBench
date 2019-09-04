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
struct sway_workspace {int dummy; } ;
struct sway_seat {scalar_t__ prev_workspace_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  _workspace_by_name ; 
 struct sway_seat* input_manager_current_seat () ; 
 struct sway_workspace* root_find_workspace (int /*<<< orphan*/ ,void*) ; 
 struct sway_workspace* seat_get_focused_workspace (struct sway_seat*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 struct sway_workspace* workspace_next (struct sway_workspace*) ; 
 struct sway_workspace* workspace_output_next (struct sway_workspace*,int) ; 
 struct sway_workspace* workspace_output_prev (struct sway_workspace*,int) ; 
 struct sway_workspace* workspace_prev (struct sway_workspace*) ; 

struct sway_workspace *workspace_by_name(const char *name) {
	struct sway_seat *seat = input_manager_current_seat();
	struct sway_workspace *current = seat_get_focused_workspace(seat);

	if (current && strcmp(name, "prev") == 0) {
		return workspace_prev(current);
	} else if (current && strcmp(name, "prev_on_output") == 0) {
		return workspace_output_prev(current, false);
	} else if (current && strcmp(name, "next") == 0) {
		return workspace_next(current);
	} else if (current && strcmp(name, "next_on_output") == 0) {
		return workspace_output_next(current, false);
	} else if (strcmp(name, "current") == 0) {
		return current;
	} else if (strcasecmp(name, "back_and_forth") == 0) {
		struct sway_seat *seat = input_manager_current_seat();
		if (!seat->prev_workspace_name) {
			return NULL;
		}
		return root_find_workspace(_workspace_by_name,
				(void*)seat->prev_workspace_name);
	} else {
		return root_find_workspace(_workspace_by_name, (void*)name);
	}
}