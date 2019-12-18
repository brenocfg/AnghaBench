#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int priority; } ;
struct TYPE_5__ {int priority; } ;
struct TYPE_7__ {TYPE_2__ parameters_fragment; scalar_t__ from_fragment; TYPE_1__ parameters_proc_swaps; scalar_t__ from_proc_swaps; } ;
typedef  TYPE_3__ Swap ;

/* Variables and functions */

__attribute__((used)) static int swap_get_priority(Swap *s) {
        if (s->from_proc_swaps)
                return s->parameters_proc_swaps.priority;
        if (s->from_fragment)
                return s->parameters_fragment.priority;
        return -1;
}