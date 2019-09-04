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
struct sway_transaction_instruction {scalar_t__ timer; TYPE_1__* instructions; struct sway_node* node; } ;
struct sway_transaction {scalar_t__ timer; TYPE_1__* instructions; struct sway_node* node; } ;
struct sway_node {scalar_t__ ntxnrefs; int type; int /*<<< orphan*/  sway_container; int /*<<< orphan*/  sway_workspace; int /*<<< orphan*/  sway_output; scalar_t__ destroying; struct sway_transaction_instruction* instruction; } ;
struct TYPE_2__ {int length; struct sway_transaction_instruction** items; } ;

/* Variables and functions */
#define  N_CONTAINER 131 
#define  N_OUTPUT 130 
#define  N_ROOT 129 
#define  N_WORKSPACE 128 
 int /*<<< orphan*/  container_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sway_transaction_instruction*) ; 
 int /*<<< orphan*/  list_free (TYPE_1__*) ; 
 int /*<<< orphan*/  output_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 
 int /*<<< orphan*/  wl_event_source_remove (scalar_t__) ; 
 int /*<<< orphan*/  workspace_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void transaction_destroy(struct sway_transaction *transaction) {
	// Free instructions
	for (int i = 0; i < transaction->instructions->length; ++i) {
		struct sway_transaction_instruction *instruction =
			transaction->instructions->items[i];
		struct sway_node *node = instruction->node;
		node->ntxnrefs--;
		if (node->instruction == instruction) {
			node->instruction = NULL;
		}
		if (node->destroying && node->ntxnrefs == 0) {
			switch (node->type) {
			case N_ROOT:
				sway_assert(false, "Never reached");
				break;
			case N_OUTPUT:
				output_destroy(node->sway_output);
				break;
			case N_WORKSPACE:
				workspace_destroy(node->sway_workspace);
				break;
			case N_CONTAINER:
				container_destroy(node->sway_container);
				break;
			}
		}
		free(instruction);
	}
	list_free(transaction->instructions);

	if (transaction->timer) {
		wl_event_source_remove(transaction->timer);
	}
	free(transaction);
}