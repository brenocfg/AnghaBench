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
struct timespec {int tv_sec; double tv_nsec; } ;
struct sway_transaction_instruction {int /*<<< orphan*/  container_state; int /*<<< orphan*/  workspace_state; int /*<<< orphan*/  output_state; struct sway_node* node; } ;
struct sway_transaction {TYPE_1__* instructions; struct timespec commit_time; } ;
struct sway_node {int type; int /*<<< orphan*/ * instruction; int /*<<< orphan*/  sway_container; int /*<<< orphan*/  sway_workspace; int /*<<< orphan*/  sway_output; } ;
struct TYPE_4__ {scalar_t__ txn_timings; } ;
struct TYPE_3__ {int length; struct sway_transaction_instruction** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
#define  N_CONTAINER 131 
#define  N_OUTPUT 130 
#define  N_ROOT 129 
#define  N_WORKSPACE 128 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  apply_container_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apply_output_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apply_workspace_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  cursor_rebase_all () ; 
 TYPE_2__ debug ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,struct sway_transaction*,...) ; 

__attribute__((used)) static void transaction_apply(struct sway_transaction *transaction) {
	sway_log(SWAY_DEBUG, "Applying transaction %p", transaction);
	if (debug.txn_timings) {
		struct timespec now;
		clock_gettime(CLOCK_MONOTONIC, &now);
		struct timespec *commit = &transaction->commit_time;
		float ms = (now.tv_sec - commit->tv_sec) * 1000 +
			(now.tv_nsec - commit->tv_nsec) / 1000000.0;
		sway_log(SWAY_DEBUG, "Transaction %p: %.1fms waiting "
				"(%.1f frames if 60Hz)", transaction, ms, ms / (1000.0f / 60));
	}

	// Apply the instruction state to the node's current state
	for (int i = 0; i < transaction->instructions->length; ++i) {
		struct sway_transaction_instruction *instruction =
			transaction->instructions->items[i];
		struct sway_node *node = instruction->node;

		switch (node->type) {
		case N_ROOT:
			break;
		case N_OUTPUT:
			apply_output_state(node->sway_output, &instruction->output_state);
			break;
		case N_WORKSPACE:
			apply_workspace_state(node->sway_workspace,
					&instruction->workspace_state);
			break;
		case N_CONTAINER:
			apply_container_state(node->sway_container,
					&instruction->container_state);
			break;
		}

		node->instruction = NULL;
	}

	cursor_rebase_all();
}