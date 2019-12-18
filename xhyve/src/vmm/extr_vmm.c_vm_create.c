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
struct vm {int /*<<< orphan*/  rendezvous_sleep_cnd; int /*<<< orphan*/  rendezvous_mtx; scalar_t__ num_mem_segs; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  assert (struct vm*) ; 
 int /*<<< orphan*/  bzero (struct vm*,int) ; 
 struct vm* malloc (int) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_init (struct vm*,int) ; 
 int /*<<< orphan*/  vmm_initialized ; 

int
vm_create(struct vm **retvm)
{
	struct vm *vm;

	if (!vmm_initialized)
		return (ENXIO);

	vm = malloc(sizeof(struct vm));
	assert(vm);
	bzero(vm, sizeof(struct vm));
	vm->num_mem_segs = 0;
	pthread_mutex_init(&vm->rendezvous_mtx, NULL);
	pthread_cond_init(&vm->rendezvous_sleep_cnd, NULL);

	vm_init(vm, true);

	*retvm = vm;
	return (0);
}