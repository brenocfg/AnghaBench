#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int allocated; int /*<<< orphan*/  set; } ;
typedef  TYPE_1__ CPUSet ;

/* Variables and functions */
 scalar_t__ CPU_ISSET_S (unsigned int,int,int /*<<< orphan*/ ) ; 
 int cpu_set_add (TYPE_1__*,unsigned int) ; 

int cpu_set_add_all(CPUSet *a, const CPUSet *b) {
        int r;

        /* Do this backwards, so if we fail, we fail before changing anything. */
        for (unsigned cpu_p1 = b->allocated * 8; cpu_p1 > 0; cpu_p1--)
                if (CPU_ISSET_S(cpu_p1 - 1, b->allocated, b->set)) {
                        r = cpu_set_add(a, cpu_p1 - 1);
                        if (r < 0)
                                return r;
                }

        return 0;
}