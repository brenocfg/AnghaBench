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
struct sway_node {int type; TYPE_2__* sway_workspace; TYPE_1__* sway_container; } ;
typedef  int /*<<< orphan*/  list_t ;
struct TYPE_4__ {int /*<<< orphan*/ * tiling; } ;
struct TYPE_3__ {int /*<<< orphan*/ * children; } ;

/* Variables and functions */
#define  N_CONTAINER 131 
#define  N_OUTPUT 130 
#define  N_ROOT 129 
#define  N_WORKSPACE 128 

list_t *node_get_children(struct sway_node *node) {
	switch (node->type) {
	case N_CONTAINER:
		return node->sway_container->children;
	case N_WORKSPACE:
		return node->sway_workspace->tiling;
	case N_OUTPUT:
	case N_ROOT:
		return NULL;
	}
	return NULL;
}