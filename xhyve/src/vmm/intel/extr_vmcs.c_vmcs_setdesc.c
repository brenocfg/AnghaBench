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
typedef  scalar_t__ uint32_t ;
struct seg_desc {int /*<<< orphan*/  access; int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ VMCS_INVALID_ENCODING ; 
 int vmcs_seg_desc_encoding (int,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  vmcs_write (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhyve_abort (char*,int) ; 

int
vmcs_setdesc(int vcpuid, int seg, struct seg_desc *desc)
{
	int error;
	uint32_t base, limit, access;

	error = vmcs_seg_desc_encoding(seg, &base, &limit, &access);
	if (error != 0)
		xhyve_abort("vmcs_setdesc: invalid segment register %d\n", seg);

	vmcs_write(vcpuid, base, desc->base);
	vmcs_write(vcpuid, limit, desc->limit);
	if (access != VMCS_INVALID_ENCODING) {
		vmcs_write(vcpuid, access, desc->access);
	}

	return (0);
}