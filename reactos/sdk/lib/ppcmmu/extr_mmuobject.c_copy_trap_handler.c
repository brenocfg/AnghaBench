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
typedef  int paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetPhys (int,int) ; 
 scalar_t__ _mmumain ; 
 int* trap_end ; 
 int* trap_start ; 

void copy_trap_handler(int trap)
{
    int i;
    paddr_t targetArea = trap * 0x100;

    /* Set target addr */
    trap_end[0] = (int)_mmumain;

    for (i = 0; i <= trap_end - trap_start; i++)
    {
        SetPhys(targetArea + (i * sizeof(int)), trap_start[i]);
    }
}