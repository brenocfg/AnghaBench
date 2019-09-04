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
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vm_guest_paging {int cpu_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  vie; int /*<<< orphan*/  cs_d; void* cs_base; void* gla; void* gpa; struct vm_guest_paging paging; } ;
struct TYPE_4__ {TYPE_1__ inst_emul; } ;
struct vm_exit {TYPE_2__ u; int /*<<< orphan*/  exitcode; } ;

/* Variables and functions */
#define  CPU_MODE_64BIT 131 
#define  CPU_MODE_COMPATIBILITY 130 
#define  CPU_MODE_PROTECTED 129 
#define  CPU_MODE_REAL 128 
 int /*<<< orphan*/  SEG_DESC_DEF32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMCS_GUEST_CS_ACCESS_RIGHTS ; 
 int /*<<< orphan*/  VMCS_GUEST_CS_BASE ; 
 int /*<<< orphan*/  VM_EXITCODE_INST_EMUL ; 
 int /*<<< orphan*/  vie_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* vmcs_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_paging_info (struct vm_guest_paging*,int) ; 

__attribute__((used)) static void
vmexit_inst_emul(struct vm_exit *vmexit, uint64_t gpa, uint64_t gla, int vcpu)
{
	struct vm_guest_paging *paging;
	uint32_t csar;

	paging = &vmexit->u.inst_emul.paging;

	vmexit->exitcode = VM_EXITCODE_INST_EMUL;
	vmexit->u.inst_emul.gpa = gpa;
	vmexit->u.inst_emul.gla = gla;
	vmx_paging_info(paging, vcpu);
	switch (paging->cpu_mode) {
	case CPU_MODE_REAL:
		vmexit->u.inst_emul.cs_base = vmcs_read(vcpu, VMCS_GUEST_CS_BASE);
		vmexit->u.inst_emul.cs_d = 0;
		break;
	case CPU_MODE_PROTECTED:
	case CPU_MODE_COMPATIBILITY:
		vmexit->u.inst_emul.cs_base = vmcs_read(vcpu, VMCS_GUEST_CS_BASE);
		csar = (uint32_t) vmcs_read(vcpu, VMCS_GUEST_CS_ACCESS_RIGHTS);
		vmexit->u.inst_emul.cs_d = SEG_DESC_DEF32(csar);
		break;
	case CPU_MODE_64BIT:
		vmexit->u.inst_emul.cs_base = 0;
		vmexit->u.inst_emul.cs_d = 0;
		break;
	}
	vie_init(&vmexit->u.inst_emul.vie, NULL, 0);
}