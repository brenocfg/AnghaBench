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
struct sway_transaction_instruction {scalar_t__ node; } ;
struct sway_transaction {TYPE_1__* instructions; } ;
struct TYPE_2__ {scalar_t__ length; struct sway_transaction_instruction** items; } ;

/* Variables and functions */

__attribute__((used)) static bool transaction_same_nodes(struct sway_transaction *a,
		struct sway_transaction *b) {
	if (a->instructions->length != b->instructions->length) {
		return false;
	}
	for (int i = 0; i < a->instructions->length; ++i) {
		struct sway_transaction_instruction *a_inst = a->instructions->items[i];
		struct sway_transaction_instruction *b_inst = b->instructions->items[i];
		if (a_inst->node != b_inst->node) {
			return false;
		}
	}
	return true;
}