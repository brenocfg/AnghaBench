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
struct sway_transaction {scalar_t__ num_waiting; } ;
struct TYPE_4__ {int length; struct sway_transaction** items; } ;
struct TYPE_3__ {TYPE_2__* transactions; int /*<<< orphan*/  idle_inhibit_manager_v1; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  sway_idle_inhibit_v1_check_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transaction_apply (struct sway_transaction*) ; 
 int /*<<< orphan*/  transaction_commit (struct sway_transaction*) ; 
 int /*<<< orphan*/  transaction_destroy (struct sway_transaction*) ; 
 scalar_t__ transaction_same_nodes (struct sway_transaction*,struct sway_transaction*) ; 

__attribute__((used)) static void transaction_progress_queue(void) {
	if (!server.transactions->length) {
		return;
	}
	// There's only ever one committed transaction,
	// and it's the first one in the queue.
	struct sway_transaction *transaction = server.transactions->items[0];
	if (transaction->num_waiting) {
		return;
	}
	transaction_apply(transaction);
	transaction_destroy(transaction);
	list_del(server.transactions, 0);

	if (!server.transactions->length) {
		sway_idle_inhibit_v1_check_active(server.idle_inhibit_manager_v1);
		return;
	}

	// If there's a bunch of consecutive transactions which all apply to the
	// same views, skip all except the last one.
	while (server.transactions->length >= 2) {
		struct sway_transaction *a = server.transactions->items[0];
		struct sway_transaction *b = server.transactions->items[1];
		if (transaction_same_nodes(a, b)) {
			list_del(server.transactions, 0);
			transaction_destroy(a);
		} else {
			break;
		}
	}

	transaction = server.transactions->items[0];
	transaction_commit(transaction);
	transaction_progress_queue();
}