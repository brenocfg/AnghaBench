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

/* Variables and functions */
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 

void InvalidateLB(void)
{
	ENTER_FUNC();
    __asm__ __volatile__
	(
		"wbinvd\n\t \
		mov %%cr3,%%ecx\n\t \
        mov %%ecx,%%cr3"
        :::"ecx"
    );
	LEAVE_FUNC();
}