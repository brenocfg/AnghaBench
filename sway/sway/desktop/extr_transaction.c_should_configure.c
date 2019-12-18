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
struct sway_container_state {scalar_t__ content_x; scalar_t__ content_y; scalar_t__ content_width; scalar_t__ content_height; } ;
struct sway_transaction_instruction {struct sway_container_state container_state; } ;
struct sway_node {TYPE_2__* sway_container; scalar_t__ destroying; } ;
struct TYPE_4__ {TYPE_1__* view; struct sway_container_state current; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ SWAY_VIEW_XWAYLAND ; 
 int /*<<< orphan*/  node_is_view (struct sway_node*) ; 

__attribute__((used)) static bool should_configure(struct sway_node *node,
		struct sway_transaction_instruction *instruction) {
	if (!node_is_view(node)) {
		return false;
	}
	if (node->destroying) {
		return false;
	}
	struct sway_container_state *cstate = &node->sway_container->current;
	struct sway_container_state *istate = &instruction->container_state;
#if HAVE_XWAYLAND
	// Xwayland views are position-aware and need to be reconfigured
	// when their position changes.
	if (node->sway_container->view->type == SWAY_VIEW_XWAYLAND) {
		if (cstate->content_x != istate->content_x ||
				cstate->content_y != istate->content_y) {
			return true;
		}
	}
#endif
	if (cstate->content_width == istate->content_width &&
			cstate->content_height == istate->content_height) {
		return false;
	}
	return true;
}