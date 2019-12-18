#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  cpu_set_t ;
struct TYPE_4__ {size_t allocated; int /*<<< orphan*/ * set; } ;
typedef  TYPE_1__ CPUSet ;

/* Variables and functions */
 size_t CPU_ALLOC_SIZE (unsigned int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 

int cpu_set_realloc(CPUSet *cpu_set, unsigned ncpus) {
        size_t need;

        assert(cpu_set);

        need = CPU_ALLOC_SIZE(ncpus);
        if (need > cpu_set->allocated) {
                cpu_set_t *t;

                t = realloc(cpu_set->set, need);
                if (!t)
                        return -ENOMEM;

                memzero((uint8_t*) t + cpu_set->allocated, need - cpu_set->allocated);

                cpu_set->set = t;
                cpu_set->allocated = need;
        }

        return 0;
}