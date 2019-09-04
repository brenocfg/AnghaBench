#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sway_node {int type; int /*<<< orphan*/  sway_container; int /*<<< orphan*/  sway_workspace; int /*<<< orphan*/  sway_output; } ;

/* Variables and functions */
#define  N_CONTAINER 131 
#define  N_OUTPUT 130 
#define  N_ROOT 129 
#define  N_WORKSPACE 128 
 int /*<<< orphan*/  arrange_container (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arrange_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arrange_root () ; 
 int /*<<< orphan*/  arrange_workspace (int /*<<< orphan*/ ) ; 

void arrange_node(struct sway_node *node) {
	switch (node->type) {
	case N_ROOT:
		arrange_root();
		break;
	case N_OUTPUT:
		arrange_output(node->sway_output);
		break;
	case N_WORKSPACE:
		arrange_workspace(node->sway_workspace);
		break;
	case N_CONTAINER:
		arrange_container(node->sway_container);
		break;
	}
}