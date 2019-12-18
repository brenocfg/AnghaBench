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
typedef  int uint64_t ;
typedef  enum exc_class { ____Placeholder_exc_class } exc_class ;

/* Variables and functions */
 int EXC_BENIGN ; 
 int EXC_CONTRIBUTORY ; 
 int EXC_PAGEFAULT ; 
#define  IDT_DE 137 
#define  IDT_GP 136 
#define  IDT_NP 135 
#define  IDT_PF 134 
#define  IDT_SS 133 
#define  IDT_TS 132 
#define  IDT_VE 131 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
#define  VM_INTINFO_HWINTR 130 
#define  VM_INTINFO_NMI 129 
#define  VM_INTINFO_SWINTR 128 
 int VM_INTINFO_TYPE ; 
 int VM_INTINFO_VALID ; 

__attribute__((used)) static enum exc_class
exception_class(uint64_t info)
{
	int type, vector;

	KASSERT(info & VM_INTINFO_VALID, ("intinfo must be valid: %#llx", info));
	type = info & VM_INTINFO_TYPE;
	vector = info & 0xff;

	/* Table 6-4, "Interrupt and Exception Classes", Intel SDM, Vol 3 */
	switch (type) {
	case VM_INTINFO_HWINTR:
	case VM_INTINFO_SWINTR:
	case VM_INTINFO_NMI:
		return (EXC_BENIGN);
	default:
		/*
		 * Hardware exception.
		 *
		 * SVM and VT-x use identical type values to represent NMI,
		 * hardware interrupt and software interrupt.
		 *
		 * SVM uses type '3' for all exceptions. VT-x uses type '3'
		 * for exceptions except #BP and #OF. #BP and #OF use a type
		 * value of '5' or '6'. Therefore we don't check for explicit
		 * values of 'type' to classify 'intinfo' into a hardware
		 * exception.
		 */
		break;
	}

	switch (vector) {
	case IDT_PF:
	case IDT_VE:
		return (EXC_PAGEFAULT);
	case IDT_DE:
	case IDT_TS:
	case IDT_NP:
	case IDT_SS:
	case IDT_GP:
		return (EXC_CONTRIBUTORY);
	default:
		return (EXC_BENIGN);
	}
}