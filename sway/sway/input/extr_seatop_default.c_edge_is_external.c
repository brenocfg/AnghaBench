#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sway_container {struct sway_container* parent; } ;
struct TYPE_4__ {int length; } ;
typedef  TYPE_1__ list_t ;
typedef  enum wlr_edges { ____Placeholder_wlr_edges } wlr_edges ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;

/* Variables and functions */
 int L_HORIZ ; 
 int L_NONE ; 
 int L_VERT ; 
#define  WLR_EDGE_BOTTOM 132 
#define  WLR_EDGE_LEFT 131 
#define  WLR_EDGE_NONE 130 
#define  WLR_EDGE_RIGHT 129 
#define  WLR_EDGE_TOP 128 
 TYPE_1__* container_get_siblings (struct sway_container*) ; 
 int container_parent_layout (struct sway_container*) ; 
 int list_find (TYPE_1__*,struct sway_container*) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 

__attribute__((used)) static bool edge_is_external(struct sway_container *cont, enum wlr_edges edge) {
	enum sway_container_layout layout = L_NONE;
	switch (edge) {
	case WLR_EDGE_TOP:
	case WLR_EDGE_BOTTOM:
		layout = L_VERT;
		break;
	case WLR_EDGE_LEFT:
	case WLR_EDGE_RIGHT:
		layout = L_HORIZ;
		break;
	case WLR_EDGE_NONE:
		sway_assert(false, "Never reached");
		return false;
	}

	// Iterate the parents until we find one with the layout we want,
	// then check if the child has siblings between it and the edge.
	while (cont) {
		if (container_parent_layout(cont) == layout) {
			list_t *siblings = container_get_siblings(cont);
			int index = list_find(siblings, cont);
			if (index > 0 && (edge == WLR_EDGE_LEFT || edge == WLR_EDGE_TOP)) {
				return false;
			}
			if (index < siblings->length - 1 &&
					(edge == WLR_EDGE_RIGHT || edge == WLR_EDGE_BOTTOM)) {
				return false;
			}
		}
		cont = cont->parent;
	}
	return true;
}