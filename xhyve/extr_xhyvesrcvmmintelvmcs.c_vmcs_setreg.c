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
typedef  int uint32_t ;

/* Variables and functions */
 int EINVAL ; 
 int vmcs_field_encoding (int) ; 
 int /*<<< orphan*/  vmcs_fix_regval (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write (int,int,int /*<<< orphan*/ ) ; 

int
vmcs_setreg(int vcpuid, int ident, uint64_t val)
{
	uint32_t encoding;

	if (ident < 0)
		encoding = ident & 0x7fffffff;
	else
		encoding = vmcs_field_encoding(ident);

	if (encoding == (uint32_t)-1)
		return (EINVAL);

	val = vmcs_fix_regval(encoding, val);

	vmcs_write(vcpuid, encoding, val);

	return (0);
}