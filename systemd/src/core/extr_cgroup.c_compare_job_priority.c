#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int type; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {TYPE_2__* unit; } ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int CMP (int,int) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int unit_get_cpu_weight (TYPE_2__*) ; 
 int unit_get_nice (TYPE_2__*) ; 

int compare_job_priority(const void *a, const void *b) {
        const Job *x = a, *y = b;
        int nice_x, nice_y;
        uint64_t weight_x, weight_y;
        int ret;

        if ((ret = CMP(x->unit->type, y->unit->type)) != 0)
                return -ret;

        weight_x = unit_get_cpu_weight(x->unit);
        weight_y = unit_get_cpu_weight(y->unit);

        if ((ret = CMP(weight_x, weight_y)) != 0)
                return -ret;

        nice_x = unit_get_nice(x->unit);
        nice_y = unit_get_nice(y->unit);

        if ((ret = CMP(nice_x, nice_y)) != 0)
                return ret;

        return strcmp(x->unit->id, y->unit->id);
}