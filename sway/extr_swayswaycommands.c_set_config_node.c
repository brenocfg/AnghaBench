#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sway_node {int type; int /*<<< orphan*/ * sway_workspace; TYPE_1__* sway_container; } ;
struct TYPE_5__ {int /*<<< orphan*/ * workspace; TYPE_1__* container; struct sway_node* node; } ;
struct TYPE_6__ {TYPE_2__ handler_context; } ;
struct TYPE_4__ {int /*<<< orphan*/ * workspace; } ;

/* Variables and functions */
#define  N_CONTAINER 131 
#define  N_OUTPUT 130 
#define  N_ROOT 129 
#define  N_WORKSPACE 128 
 TYPE_3__* config ; 

__attribute__((used)) static void set_config_node(struct sway_node *node) {
	config->handler_context.node = node;
	config->handler_context.container = NULL;
	config->handler_context.workspace = NULL;

	if (node == NULL) {
		return;
	}

	switch (node->type) {
	case N_CONTAINER:
		config->handler_context.container = node->sway_container;
		config->handler_context.workspace = node->sway_container->workspace;
		break;
	case N_WORKSPACE:
		config->handler_context.workspace = node->sway_workspace;
		break;
	case N_ROOT:
	case N_OUTPUT:
		break;
	}
}