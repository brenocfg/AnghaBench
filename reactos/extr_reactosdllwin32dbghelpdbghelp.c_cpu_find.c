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
struct cpu {scalar_t__ machine; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 struct cpu** dbghelp_cpus ; 

struct cpu* cpu_find(DWORD machine)
{
    struct cpu** cpu;

    for (cpu = dbghelp_cpus ; *cpu; cpu++)
    {
        if (cpu[0]->machine == machine) return cpu[0];
    }
    return NULL;
}