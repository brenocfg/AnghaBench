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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  void* uint32_t ;
struct seg_desc {void* access; void* limit; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  vcpu_freeze (int,int) ; 
 int /*<<< orphan*/  vm ; 
 int vm_set_seg_desc (int /*<<< orphan*/ ,int,int,struct seg_desc*) ; 

int
xh_vm_set_desc(int vcpu, int reg, uint64_t base, uint32_t limit,
	uint32_t access)
{
	struct seg_desc sd;
	int error;

	sd.base = base;
	sd.limit = limit;
	sd.access = access;
	vcpu_freeze(vcpu, true);
	error = vm_set_seg_desc(vm, vcpu, reg, &sd);
	vcpu_freeze(vcpu, false);

	return (error);
}