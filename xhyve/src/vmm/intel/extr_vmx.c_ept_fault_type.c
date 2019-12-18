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

/* Variables and functions */
 int EPT_VIOLATION_DATA_WRITE ; 
 int EPT_VIOLATION_INST_FETCH ; 
 int XHYVE_PROT_EXECUTE ; 
 int XHYVE_PROT_READ ; 
 int XHYVE_PROT_WRITE ; 

__attribute__((used)) static int
ept_fault_type(uint64_t ept_qual)
{
	int fault_type;

	if (ept_qual & EPT_VIOLATION_DATA_WRITE)
		fault_type = XHYVE_PROT_WRITE;
	else if (ept_qual & EPT_VIOLATION_INST_FETCH)
		fault_type = XHYVE_PROT_EXECUTE;
	else
		fault_type= XHYVE_PROT_READ;

	return (fault_type);
}