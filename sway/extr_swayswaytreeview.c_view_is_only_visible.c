#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sway_view {struct sway_container* container; } ;
struct sway_container {struct sway_container* parent; } ;
struct TYPE_3__ {int length; } ;
typedef  TYPE_1__ list_t ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;

/* Variables and functions */
 int L_STACKED ; 
 int L_TABBED ; 
 TYPE_1__* container_get_siblings (struct sway_container*) ; 
 int container_parent_layout (struct sway_container*) ; 

bool view_is_only_visible(struct sway_view *view) {
	bool only_view = true;
	struct sway_container *con = view->container;
	while (con) {
		enum sway_container_layout layout = container_parent_layout(con);
		if (layout != L_TABBED && layout != L_STACKED) {
			list_t *siblings = container_get_siblings(con);
			if (siblings && siblings->length > 1) {
				only_view = false;
				break;
			}
		}
		con = con->parent;
	}
	return only_view;
}