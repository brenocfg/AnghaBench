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
struct TYPE_4__ {int code; int /*<<< orphan*/  wval; } ;
struct TYPE_3__ {TYPE_2__ msr; } ;
struct vm_exit {TYPE_1__ u; } ;

/* Variables and functions */
 int VMEXIT_CONTINUE ; 
 int emulate_wrmsr (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strictmsr ; 
 int /*<<< orphan*/  vm_inject_gp (int) ; 

__attribute__((used)) static int
vmexit_wrmsr(struct vm_exit *vme, int *pvcpu)
{
	int error;

	error = emulate_wrmsr(*pvcpu, vme->u.msr.code, vme->u.msr.wval);
	if (error != 0) {
		fprintf(stderr, "wrmsr to register %#x(%#llx) on vcpu %d\n",
		    vme->u.msr.code, vme->u.msr.wval, *pvcpu);
		if (strictmsr) {
			vm_inject_gp(*pvcpu);
			return (VMEXIT_CONTINUE);
		}
	}
	return (VMEXIT_CONTINUE);
}