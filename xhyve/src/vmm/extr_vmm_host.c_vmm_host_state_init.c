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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int xsave_enabled; scalar_t__ xsave_max_size; int /*<<< orphan*/  xcr0_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFEATURE_AVX ; 
 int /*<<< orphan*/  cpuid_count (int,int,scalar_t__*) ; 
 int /*<<< orphan*/  sysctlbyname (char*,scalar_t__*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ vmm_xsave_limits ; 

void
vmm_host_state_init(void)
{
	uint32_t avx1_0, regs[4];
	size_t ln;

	vmm_xsave_limits.xsave_enabled = 0;

	ln = sizeof(uint32_t);
	if (!sysctlbyname("hw.optional.avx1_0", &avx1_0, &ln, NULL, 0) && avx1_0) {
		cpuid_count(0xd, 0x0, regs);
		vmm_xsave_limits.xsave_enabled = 1;
		vmm_xsave_limits.xcr0_allowed = XFEATURE_AVX;
		vmm_xsave_limits.xsave_max_size = regs[1];
	}
}