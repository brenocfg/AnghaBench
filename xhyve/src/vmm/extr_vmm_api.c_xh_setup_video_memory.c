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

/* Variables and functions */
 size_t XHYVE_PAGE_SIZE ; 
 int XHYVE_PROT_READ ; 
 int XHYVE_PROT_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int setup_memory_segment (int /*<<< orphan*/ ,size_t,int,void**) ; 

int
xh_setup_video_memory(uint64_t gpa, size_t len, void **addr)
{
    int error;

    assert(len % XHYVE_PAGE_SIZE == 0);

    /* place video memory and mark it non-executable */
    error = setup_memory_segment(gpa, len, XHYVE_PROT_READ | XHYVE_PROT_WRITE, addr);

    return error;
}