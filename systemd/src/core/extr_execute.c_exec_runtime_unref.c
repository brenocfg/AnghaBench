#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ n_ref; } ;
typedef  TYPE_1__ ExecRuntime ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* exec_runtime_free (TYPE_1__*,int) ; 

ExecRuntime *exec_runtime_unref(ExecRuntime *rt, bool destroy) {
        if (!rt)
                return NULL;

        assert(rt->n_ref > 0);

        rt->n_ref--;
        if (rt->n_ref > 0)
                return NULL;

        return exec_runtime_free(rt, destroy);
}