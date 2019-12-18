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
typedef  scalar_t__ uint64_t ;
struct vlapic {scalar_t__ msr_apicbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLAPIC_CTR2 (struct vlapic*,char*,scalar_t__,scalar_t__) ; 

int
vlapic_set_apicbase(struct vlapic *vlapic, uint64_t new)
{

	if (vlapic->msr_apicbase != new) {
		VLAPIC_CTR2(vlapic, "Changing APIC_BASE MSR from %#llx to %#llx "
		    "not supported", vlapic->msr_apicbase, new);
		return (-1);
	}

	return (0);
}