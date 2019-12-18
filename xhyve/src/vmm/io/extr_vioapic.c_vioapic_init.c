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
struct vm {int dummy; } ;
struct vioapic {TYPE_1__* rtbl; struct vm* vm; } ;
struct TYPE_2__ {int reg; } ;

/* Variables and functions */
 int REDIR_ENTRIES ; 
 int /*<<< orphan*/  VIOAPIC_LOCK_INIT (struct vioapic*) ; 
 int /*<<< orphan*/  assert (struct vioapic*) ; 
 int /*<<< orphan*/  bzero (struct vioapic*,int) ; 
 struct vioapic* malloc (int) ; 

struct vioapic *
vioapic_init(struct vm *vm)
{
	int i;
	struct vioapic *vioapic;

	vioapic = malloc(sizeof(struct vioapic));
	assert(vioapic);
	bzero(vioapic, sizeof(struct vioapic));
	vioapic->vm = vm;

	VIOAPIC_LOCK_INIT(vioapic);

	/* Initialize all redirection entries to mask all interrupts */
	for (i = 0; i < REDIR_ENTRIES; i++)
		vioapic->rtbl[i].reg = 0x0001000000010000UL;

	return (vioapic);
}