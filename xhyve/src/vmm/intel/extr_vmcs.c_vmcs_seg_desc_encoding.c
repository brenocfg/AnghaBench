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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VMCS_GUEST_CS_ACCESS_RIGHTS ; 
 int /*<<< orphan*/  VMCS_GUEST_CS_BASE ; 
 int /*<<< orphan*/  VMCS_GUEST_CS_LIMIT ; 
 int /*<<< orphan*/  VMCS_GUEST_DS_ACCESS_RIGHTS ; 
 int /*<<< orphan*/  VMCS_GUEST_DS_BASE ; 
 int /*<<< orphan*/  VMCS_GUEST_DS_LIMIT ; 
 int /*<<< orphan*/  VMCS_GUEST_ES_ACCESS_RIGHTS ; 
 int /*<<< orphan*/  VMCS_GUEST_ES_BASE ; 
 int /*<<< orphan*/  VMCS_GUEST_ES_LIMIT ; 
 int /*<<< orphan*/  VMCS_GUEST_FS_ACCESS_RIGHTS ; 
 int /*<<< orphan*/  VMCS_GUEST_FS_BASE ; 
 int /*<<< orphan*/  VMCS_GUEST_FS_LIMIT ; 
 int /*<<< orphan*/  VMCS_GUEST_GDTR_BASE ; 
 int /*<<< orphan*/  VMCS_GUEST_GDTR_LIMIT ; 
 int /*<<< orphan*/  VMCS_GUEST_GS_ACCESS_RIGHTS ; 
 int /*<<< orphan*/  VMCS_GUEST_GS_BASE ; 
 int /*<<< orphan*/  VMCS_GUEST_GS_LIMIT ; 
 int /*<<< orphan*/  VMCS_GUEST_IDTR_BASE ; 
 int /*<<< orphan*/  VMCS_GUEST_IDTR_LIMIT ; 
 int /*<<< orphan*/  VMCS_GUEST_LDTR_ACCESS_RIGHTS ; 
 int /*<<< orphan*/  VMCS_GUEST_LDTR_BASE ; 
 int /*<<< orphan*/  VMCS_GUEST_LDTR_LIMIT ; 
 int /*<<< orphan*/  VMCS_GUEST_SS_ACCESS_RIGHTS ; 
 int /*<<< orphan*/  VMCS_GUEST_SS_BASE ; 
 int /*<<< orphan*/  VMCS_GUEST_SS_LIMIT ; 
 int /*<<< orphan*/  VMCS_GUEST_TR_ACCESS_RIGHTS ; 
 int /*<<< orphan*/  VMCS_GUEST_TR_BASE ; 
 int /*<<< orphan*/  VMCS_GUEST_TR_LIMIT ; 
 int /*<<< orphan*/  VMCS_INVALID_ENCODING ; 
#define  VM_REG_GUEST_CS 137 
#define  VM_REG_GUEST_DS 136 
#define  VM_REG_GUEST_ES 135 
#define  VM_REG_GUEST_FS 134 
#define  VM_REG_GUEST_GDTR 133 
#define  VM_REG_GUEST_GS 132 
#define  VM_REG_GUEST_IDTR 131 
#define  VM_REG_GUEST_LDTR 130 
#define  VM_REG_GUEST_SS 129 
#define  VM_REG_GUEST_TR 128 

__attribute__((used)) static int
vmcs_seg_desc_encoding(int seg, uint32_t *base, uint32_t *lim, uint32_t *acc)
{

	switch (seg) {
	case VM_REG_GUEST_ES:
		*base = VMCS_GUEST_ES_BASE;
		*lim = VMCS_GUEST_ES_LIMIT;
		*acc = VMCS_GUEST_ES_ACCESS_RIGHTS;
		break;
	case VM_REG_GUEST_CS:
		*base = VMCS_GUEST_CS_BASE;
		*lim = VMCS_GUEST_CS_LIMIT;
		*acc = VMCS_GUEST_CS_ACCESS_RIGHTS;
		break;
	case VM_REG_GUEST_SS:
		*base = VMCS_GUEST_SS_BASE;
		*lim = VMCS_GUEST_SS_LIMIT;
		*acc = VMCS_GUEST_SS_ACCESS_RIGHTS;
		break;
	case VM_REG_GUEST_DS:
		*base = VMCS_GUEST_DS_BASE;
		*lim = VMCS_GUEST_DS_LIMIT;
		*acc = VMCS_GUEST_DS_ACCESS_RIGHTS;
		break;
	case VM_REG_GUEST_FS:
		*base = VMCS_GUEST_FS_BASE;
		*lim = VMCS_GUEST_FS_LIMIT;
		*acc = VMCS_GUEST_FS_ACCESS_RIGHTS;
		break;
	case VM_REG_GUEST_GS:
		*base = VMCS_GUEST_GS_BASE;
		*lim = VMCS_GUEST_GS_LIMIT;
		*acc = VMCS_GUEST_GS_ACCESS_RIGHTS;
		break;
	case VM_REG_GUEST_TR:
		*base = VMCS_GUEST_TR_BASE;
		*lim = VMCS_GUEST_TR_LIMIT;
		*acc = VMCS_GUEST_TR_ACCESS_RIGHTS;
		break;
	case VM_REG_GUEST_LDTR:
		*base = VMCS_GUEST_LDTR_BASE;
		*lim = VMCS_GUEST_LDTR_LIMIT;
		*acc = VMCS_GUEST_LDTR_ACCESS_RIGHTS;
		break;
	case VM_REG_GUEST_IDTR:
		*base = VMCS_GUEST_IDTR_BASE;
		*lim = VMCS_GUEST_IDTR_LIMIT;
		*acc = VMCS_INVALID_ENCODING;
		break;
	case VM_REG_GUEST_GDTR:
		*base = VMCS_GUEST_GDTR_BASE;
		*lim = VMCS_GUEST_GDTR_LIMIT;
		*acc = VMCS_INVALID_ENCODING;
		break;
	default:
		return (EINVAL);
	}

	return (0);
}