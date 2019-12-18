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
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 size_t XHYVE_PAGE_SIZE ; 
 int XHYVE_PROT_EXECUTE ; 
 int XHYVE_PROT_READ ; 
 int /*<<< orphan*/  assert (int) ; 
 int setup_memory_segment (unsigned long long,size_t,int,void**) ; 

int
xh_setup_bootrom_memory(size_t len, void **addr)
{
    int error;

    assert(len % XHYVE_PAGE_SIZE == 0);

    /* place the bootrom memory just below 4GB and mark it non-writeable */
    uint64_t gpa = (4ull << 30) - len;
    error = setup_memory_segment(gpa, len, XHYVE_PROT_READ | XHYVE_PROT_EXECUTE, addr);

    return error;
}