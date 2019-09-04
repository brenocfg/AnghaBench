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
struct sway_transaction {scalar_t__ num_waiting; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,struct sway_transaction*,scalar_t__) ; 
 int /*<<< orphan*/  transaction_progress_queue () ; 

__attribute__((used)) static int handle_timeout(void *data) {
	struct sway_transaction *transaction = data;
	sway_log(SWAY_DEBUG, "Transaction %p timed out (%zi waiting)",
			transaction, transaction->num_waiting);
	transaction->num_waiting = 0;
	transaction_progress_queue();
	return 0;
}