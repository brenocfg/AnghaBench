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
struct TYPE_3__ {int how; } ;
struct TYPE_4__ {TYPE_1__ suspended; } ;
struct vm_exit {TYPE_2__ u; } ;
typedef  enum vm_suspend_how { ____Placeholder_vm_suspend_how } vm_suspend_how ;

/* Variables and functions */
 int BSP ; 
 int /*<<< orphan*/  CPU_EMPTY (int /*<<< orphan*/ *) ; 
#define  VM_SUSPEND_HALT 131 
#define  VM_SUSPEND_POWEROFF 130 
#define  VM_SUSPEND_RESET 129 
#define  VM_SUSPEND_TRIPLEFAULT 128 
 int /*<<< orphan*/  cpumask ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resetcpu_cond ; 
 int /*<<< orphan*/  resetcpu_mtx ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vcpu_delete (int) ; 

__attribute__((used)) static int
vmexit_suspend(struct vm_exit *vme, int *pvcpu)
{
	enum vm_suspend_how how;

	how = vme->u.suspended.how;

	vcpu_delete(*pvcpu);

	if (*pvcpu != BSP) {
		pthread_mutex_lock(&resetcpu_mtx);
		pthread_cond_signal(&resetcpu_cond);
		pthread_mutex_unlock(&resetcpu_mtx);
		pthread_exit(NULL);
	}

	pthread_mutex_lock(&resetcpu_mtx);
	while (!CPU_EMPTY(&cpumask)) {
		pthread_cond_wait(&resetcpu_cond, &resetcpu_mtx);
	}
	pthread_mutex_unlock(&resetcpu_mtx);

	switch ((int) (how)) {
	case VM_SUSPEND_RESET:
		exit(0);
	case VM_SUSPEND_POWEROFF:
		exit(1);
	case VM_SUSPEND_HALT:
		exit(2);
	case VM_SUSPEND_TRIPLEFAULT:
		exit(3);
	default:
		fprintf(stderr, "vmexit_suspend: invalid reason %d\n", how);
		exit(100);
	}
}