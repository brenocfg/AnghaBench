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
struct TYPE_4__ {int type; int /*<<< orphan*/  nodes; } ;
typedef  TYPE_1__ NUMAPolicy ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  cpu_set_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void numa_policy_reset(NUMAPolicy *p) {
        assert(p);
        cpu_set_reset(&p->nodes);
        p->type = -1;
}