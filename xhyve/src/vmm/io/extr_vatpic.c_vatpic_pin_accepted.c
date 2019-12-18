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
struct atpic {int intr_raised; scalar_t__* acnt; int request; int aeoi; int rotate; int lowprio; int service; } ;

/* Variables and functions */

__attribute__((used)) static void
vatpic_pin_accepted(struct atpic *atpic, int pin)
{
	atpic->intr_raised = false;

	if (atpic->acnt[pin] == 0)
		atpic->request &= ~(1 << pin);

	if (atpic->aeoi == true) {
		if (atpic->rotate == true)
			atpic->lowprio = pin;
	} else {
		atpic->service |= (1 << pin);
	}
}