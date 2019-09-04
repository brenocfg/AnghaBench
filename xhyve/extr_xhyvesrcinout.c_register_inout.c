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
struct inout_port {int port; int size; int /*<<< orphan*/  arg; int /*<<< orphan*/  handler; scalar_t__ flags; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  handler; scalar_t__ flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int IOPORT_F_DEFAULT ; 
 int /*<<< orphan*/  VERIFY_IOPORT (int,int) ; 
 TYPE_1__* inout_handlers ; 

int
register_inout(struct inout_port *iop)
{
	int i;

	VERIFY_IOPORT(iop->port, iop->size);

	/*
	 * Verify that the new registration is not overwriting an already
	 * allocated i/o range.
	 */
	if ((((unsigned) iop->flags) & IOPORT_F_DEFAULT) == 0) {
		for (i = iop->port; i < iop->port + iop->size; i++) {
			if ((((unsigned) inout_handlers[i].flags) & IOPORT_F_DEFAULT) == 0)
				return (-1);
		}
	}

	for (i = iop->port; i < iop->port + iop->size; i++) {
		inout_handlers[i].name = iop->name;
		inout_handlers[i].flags = iop->flags;
		inout_handlers[i].handler = iop->handler;
		inout_handlers[i].arg = iop->arg;
	}

	return (0);
}