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
struct sway_node {scalar_t__ type; TYPE_1__* sway_container; } ;
struct TYPE_2__ {scalar_t__ fullscreen_mode; } ;

/* Variables and functions */
 scalar_t__ FULLSCREEN_GLOBAL ; 
 scalar_t__ N_CONTAINER ; 
 scalar_t__ N_ROOT ; 
 struct sway_node* node_get_parent (struct sway_node*) ; 

bool node_has_ancestor(struct sway_node *node, struct sway_node *ancestor) {
	if (ancestor->type == N_ROOT && node->type == N_CONTAINER &&
			node->sway_container->fullscreen_mode == FULLSCREEN_GLOBAL) {
		return true;
	}
	struct sway_node *parent = node_get_parent(node);
	while (parent) {
		if (parent == ancestor) {
			return true;
		}
		if (ancestor->type == N_ROOT && parent->type == N_CONTAINER &&
				parent->sway_container->fullscreen_mode == FULLSCREEN_GLOBAL) {
			return true;
		}
		parent = node_get_parent(parent);
	}
	return false;
}