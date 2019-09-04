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
typedef  scalar_t__ uint32_t ;
struct sway_view {TYPE_2__* container; } ;
struct sway_transaction_instruction {scalar_t__ serial; } ;
struct TYPE_3__ {struct sway_transaction_instruction* instruction; } ;
struct TYPE_4__ {TYPE_1__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_instruction_ready (struct sway_transaction_instruction*) ; 

void transaction_notify_view_ready_by_serial(struct sway_view *view,
		uint32_t serial) {
	struct sway_transaction_instruction *instruction =
		view->container->node.instruction;
	if (instruction->serial == serial) {
		set_instruction_ready(instruction);
	}
}