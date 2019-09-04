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
struct sway_transaction {int /*<<< orphan*/  instructions; } ;

/* Variables and functions */
 struct sway_transaction* calloc (int,int) ; 
 int /*<<< orphan*/  create_list () ; 
 int /*<<< orphan*/  sway_assert (struct sway_transaction*,char*) ; 

__attribute__((used)) static struct sway_transaction *transaction_create(void) {
	struct sway_transaction *transaction =
		calloc(1, sizeof(struct sway_transaction));
	if (!sway_assert(transaction, "Unable to allocate transaction")) {
		return NULL;
	}
	transaction->instructions = create_list();
	return transaction;
}