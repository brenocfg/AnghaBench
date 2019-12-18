#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {int dummy; } ;
struct sway_seat {int dummy; } ;
struct sway_node {scalar_t__ type; struct sway_workspace* sway_workspace; TYPE_1__* sway_container; } ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
struct TYPE_3__ {struct sway_workspace* workspace; } ;

/* Variables and functions */
 scalar_t__ N_CONTAINER ; 
 scalar_t__ N_WORKSPACE ; 
 TYPE_2__* root ; 
 struct sway_node* seat_get_focus_inactive (struct sway_seat*,int /*<<< orphan*/ *) ; 

struct sway_workspace *seat_get_focused_workspace(struct sway_seat *seat) {
	struct sway_node *focus = seat_get_focus_inactive(seat, &root->node);
	if (!focus) {
		return NULL;
	}
	if (focus->type == N_CONTAINER) {
		return focus->sway_container->workspace;
	}
	if (focus->type == N_WORKSPACE) {
		return focus->sway_workspace;
	}
	return NULL; // output doesn't have a workspace yet
}