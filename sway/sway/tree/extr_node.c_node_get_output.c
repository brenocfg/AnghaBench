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
struct sway_workspace {struct sway_output* output; } ;
struct sway_output {int dummy; } ;
struct sway_node {int type; struct sway_output* sway_output; TYPE_2__* sway_workspace; TYPE_1__* sway_container; } ;
struct TYPE_4__ {struct sway_output* output; } ;
struct TYPE_3__ {struct sway_workspace* workspace; } ;

/* Variables and functions */
#define  N_CONTAINER 131 
#define  N_OUTPUT 130 
#define  N_ROOT 129 
#define  N_WORKSPACE 128 

struct sway_output *node_get_output(struct sway_node *node) {
	switch (node->type) {
	case N_CONTAINER: {
		struct sway_workspace *ws = node->sway_container->workspace;
		return ws ? ws->output : NULL;
    }
	case N_WORKSPACE:
		return node->sway_workspace->output;
	case N_OUTPUT:
		return node->sway_output;
	case N_ROOT:
		return NULL;
	}
	return NULL;
}