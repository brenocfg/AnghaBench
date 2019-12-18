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
struct sway_transaction_instruction {struct sway_node* node; struct sway_transaction* transaction; } ;
struct sway_transaction {int /*<<< orphan*/  instructions; } ;
struct sway_node {int type; int /*<<< orphan*/  ntxnrefs; int /*<<< orphan*/  sway_container; int /*<<< orphan*/  sway_workspace; int /*<<< orphan*/  sway_output; } ;

/* Variables and functions */
#define  N_CONTAINER 131 
#define  N_OUTPUT 130 
#define  N_ROOT 129 
#define  N_WORKSPACE 128 
 struct sway_transaction_instruction* calloc (int,int) ; 
 int /*<<< orphan*/  copy_container_state (int /*<<< orphan*/ ,struct sway_transaction_instruction*) ; 
 int /*<<< orphan*/  copy_output_state (int /*<<< orphan*/ ,struct sway_transaction_instruction*) ; 
 int /*<<< orphan*/  copy_workspace_state (int /*<<< orphan*/ ,struct sway_transaction_instruction*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,struct sway_transaction_instruction*) ; 
 int /*<<< orphan*/  sway_assert (struct sway_transaction_instruction*,char*) ; 

__attribute__((used)) static void transaction_add_node(struct sway_transaction *transaction,
		struct sway_node *node) {
	struct sway_transaction_instruction *instruction =
		calloc(1, sizeof(struct sway_transaction_instruction));
	if (!sway_assert(instruction, "Unable to allocate instruction")) {
		return;
	}
	instruction->transaction = transaction;
	instruction->node = node;

	switch (node->type) {
	case N_ROOT:
		break;
	case N_OUTPUT:
		copy_output_state(node->sway_output, instruction);
		break;
	case N_WORKSPACE:
		copy_workspace_state(node->sway_workspace, instruction);
		break;
	case N_CONTAINER:
		copy_container_state(node->sway_container, instruction);
		break;
	}

	list_add(transaction->instructions, instruction);
	node->ntxnrefs++;
}