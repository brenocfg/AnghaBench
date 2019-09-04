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
struct sway_node {int type; TYPE_4__* sway_container; TYPE_3__* sway_workspace; TYPE_2__* sway_output; } ;
struct TYPE_8__ {char* title; } ;
struct TYPE_7__ {char* name; } ;
struct TYPE_6__ {TYPE_1__* wlr_output; } ;
struct TYPE_5__ {char* name; } ;

/* Variables and functions */
#define  N_CONTAINER 131 
#define  N_OUTPUT 130 
#define  N_ROOT 129 
#define  N_WORKSPACE 128 

char *node_get_name(struct sway_node *node) {
	switch (node->type) {
	case N_ROOT:
		return "root";
	case N_OUTPUT:
		return node->sway_output->wlr_output->name;
	case N_WORKSPACE:
		return node->sway_workspace->name;
	case N_CONTAINER:
		return node->sway_container->title;
	}
	return NULL;
}