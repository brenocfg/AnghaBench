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
struct sway_transaction {int dummy; } ;
struct sway_node {int dirty; } ;
struct TYPE_6__ {int length; } ;
struct TYPE_5__ {TYPE_3__* transactions; TYPE_1__* dirty_nodes; } ;
struct TYPE_4__ {int length; struct sway_node** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (TYPE_3__*,struct sway_transaction*) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  transaction_add_node (struct sway_transaction*,struct sway_node*) ; 
 int /*<<< orphan*/  transaction_commit (struct sway_transaction*) ; 
 struct sway_transaction* transaction_create () ; 
 int /*<<< orphan*/  transaction_progress_queue () ; 

void transaction_commit_dirty(void) {
	if (!server.dirty_nodes->length) {
		return;
	}
	struct sway_transaction *transaction = transaction_create();
	if (!transaction) {
		return;
	}
	for (int i = 0; i < server.dirty_nodes->length; ++i) {
		struct sway_node *node = server.dirty_nodes->items[i];
		transaction_add_node(transaction, node);
		node->dirty = false;
	}
	server.dirty_nodes->length = 0;

	list_add(server.transactions, transaction);

	// There's only ever one committed transaction,
	// and it's the first one in the queue.
	if (server.transactions->length == 1) {
		transaction_commit(transaction);
		// Attempting to progress the queue here is useful
		// if the transaction has nothing to wait for.
		transaction_progress_queue();
	}
}