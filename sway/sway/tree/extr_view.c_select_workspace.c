#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {int dummy; } ;
struct sway_view {int /*<<< orphan*/  pid; } ;
struct sway_seat {scalar_t__ prev_workspace_name; } ;
struct sway_output {int dummy; } ;
struct sway_node {scalar_t__ type; TYPE_1__* sway_container; struct sway_workspace* sway_workspace; } ;
struct criteria {int type; scalar_t__ target; } ;
struct TYPE_7__ {int length; struct criteria** items; } ;
typedef  TYPE_2__ list_t ;
struct TYPE_8__ {int /*<<< orphan*/  node; } ;
struct TYPE_6__ {struct sway_workspace* workspace; } ;

/* Variables and functions */
 int CT_ASSIGN_OUTPUT ; 
 int CT_ASSIGN_WORKSPACE ; 
 int CT_ASSIGN_WORKSPACE_NUMBER ; 
 scalar_t__ N_CONTAINER ; 
 scalar_t__ N_WORKSPACE ; 
 TYPE_2__* criteria_for_view (struct sway_view*,int) ; 
 struct sway_seat* input_manager_current_seat () ; 
 int /*<<< orphan*/  list_free (TYPE_2__*) ; 
 struct sway_output* output_by_name_or_id (scalar_t__) ; 
 struct sway_workspace* output_get_active_workspace (struct sway_output*) ; 
 TYPE_3__* root ; 
 struct sway_workspace* root_workspace_for_pid (int /*<<< orphan*/ ) ; 
 struct sway_node* seat_get_focus_inactive (struct sway_seat*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 
 struct sway_workspace* workspace_by_name (scalar_t__) ; 
 struct sway_workspace* workspace_by_number (scalar_t__) ; 
 struct sway_workspace* workspace_create (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static struct sway_workspace *select_workspace(struct sway_view *view) {
	struct sway_seat *seat = input_manager_current_seat();

	// Check if there's any `assign` criteria for the view
	list_t *criterias = criteria_for_view(view,
			CT_ASSIGN_WORKSPACE | CT_ASSIGN_WORKSPACE_NUMBER | CT_ASSIGN_OUTPUT);
	struct sway_workspace *ws = NULL;
	for (int i = 0; i < criterias->length; ++i) {
		struct criteria *criteria = criterias->items[i];
		if (criteria->type == CT_ASSIGN_OUTPUT) {
			struct sway_output *output = output_by_name_or_id(criteria->target);
			if (output) {
				ws = output_get_active_workspace(output);
				break;
			}
		} else {
			// CT_ASSIGN_WORKSPACE(_NUMBER)
			ws = criteria->type == CT_ASSIGN_WORKSPACE_NUMBER ?
				workspace_by_number(criteria->target) :
				workspace_by_name(criteria->target);

			if (!ws) {
				if (strcasecmp(criteria->target, "back_and_forth") == 0) {
					if (seat->prev_workspace_name) {
						ws = workspace_create(NULL, seat->prev_workspace_name);
					}
				} else {
					ws = workspace_create(NULL, criteria->target);
				}
			}
			break;
		}
	}
	list_free(criterias);
	if (ws) {
		return ws;
	}

	// Check if there's a PID mapping
	ws = root_workspace_for_pid(view->pid);
	if (ws) {
		return ws;
	}

	// Use the focused workspace
	struct sway_node *node = seat_get_focus_inactive(seat, &root->node);
	if (node && node->type == N_WORKSPACE) {
		return node->sway_workspace;
	} else if (node && node->type == N_CONTAINER) {
		return node->sway_container->workspace;
	}

	// When there's no outputs connected, the above should match a workspace on
	// the noop output.
	sway_assert(false, "Expected to find a workspace");
	return NULL;
}