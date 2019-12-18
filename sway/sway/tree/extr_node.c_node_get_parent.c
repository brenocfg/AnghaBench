#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {TYPE_1__* output; } ;
struct sway_node {int type; struct sway_workspace* sway_workspace; struct sway_container* sway_container; } ;
struct sway_container {TYPE_3__* workspace; TYPE_2__* parent; } ;
struct TYPE_8__ {struct sway_node node; } ;
struct TYPE_7__ {struct sway_node node; } ;
struct TYPE_6__ {struct sway_node node; } ;
struct TYPE_5__ {struct sway_node node; } ;

/* Variables and functions */
#define  N_CONTAINER 131 
#define  N_OUTPUT 130 
#define  N_ROOT 129 
#define  N_WORKSPACE 128 
 TYPE_4__* root ; 

struct sway_node *node_get_parent(struct sway_node *node) {
	switch (node->type) {
	case N_CONTAINER: {
			struct sway_container *con = node->sway_container;
			if (con->parent) {
				return &con->parent->node;
			}
			if (con->workspace) {
				return &con->workspace->node;
			}
		}
		return NULL;
	case N_WORKSPACE: {
			struct sway_workspace *ws = node->sway_workspace;
			if (ws->output) {
				return &ws->output->node;
			}
		}
		return NULL;
	case N_OUTPUT:
		return &root->node;
	case N_ROOT:
		return NULL;
	}
	return NULL;
}