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
struct vmm_stat_type {int /*<<< orphan*/  (* func ) (struct vm*,int,struct vmm_stat_type*) ;} ;
struct vm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int VM_MAXCPU ; 
 int /*<<< orphan*/  stub1 (struct vm*,int,struct vmm_stat_type*) ; 
 int /*<<< orphan*/ * vcpu_stats (struct vm*,int) ; 
 int vst_num_elems ; 
 int vst_num_types ; 
 struct vmm_stat_type** vsttab ; 

int
vmm_stat_copy(struct vm *vm, int vcpu, int *num_stats, uint64_t *buf)
{
	struct vmm_stat_type *vst;
	uint64_t *stats;
	int i;

	if (vcpu < 0 || vcpu >= VM_MAXCPU)
		return (EINVAL);

	/* Let stats functions update their counters */
	for (i = 0; i < vst_num_types; i++) {
		vst = vsttab[i];
		if (vst->func != NULL)
			(*vst->func)(vm, vcpu, vst);
	}

	/* Copy over the stats */
	stats = vcpu_stats(vm, vcpu);
	for (i = 0; i < vst_num_elems; i++)
		buf[i] = stats[i];
	*num_stats = vst_num_elems;
	return (0);
}