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
struct TYPE_4__ {int /*<<< orphan*/  path; int /*<<< orphan*/  io_valid; scalar_t__ io_output_bps; scalar_t__ io_input_bps; int /*<<< orphan*/  memory_valid; scalar_t__ memory; int /*<<< orphan*/  n_tasks_valid; scalar_t__ n_tasks; scalar_t__ cpu_usage; int /*<<< orphan*/  cpu_valid; scalar_t__ cpu_fraction; } ;
typedef  TYPE_1__ Group ;

/* Variables and functions */
 int CMP (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CPU_PERCENT ; 
#define  ORDER_CPU 132 
#define  ORDER_IO 131 
#define  ORDER_MEMORY 130 
#define  ORDER_PATH 129 
#define  ORDER_TASKS 128 
 int /*<<< orphan*/  arg_cpu_type ; 
 int arg_order ; 
 scalar_t__ arg_recursive ; 
 int /*<<< orphan*/  empty_to_root (int /*<<< orphan*/ ) ; 
 int path_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ path_startswith (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int group_compare(Group * const *a, Group * const *b) {
        const Group *x = *a, *y = *b;
        int r;

        if (arg_order != ORDER_TASKS || arg_recursive) {
                /* Let's make sure that the parent is always before
                 * the child. Except when ordering by tasks and
                 * recursive summing is off, since that is actually
                 * not accumulative for all children. */

                if (path_startswith(empty_to_root(y->path), empty_to_root(x->path)))
                        return -1;
                if (path_startswith(empty_to_root(x->path), empty_to_root(y->path)))
                        return 1;
        }

        switch (arg_order) {

        case ORDER_PATH:
                break;

        case ORDER_CPU:
                if (arg_cpu_type == CPU_PERCENT) {
                        if (x->cpu_valid && y->cpu_valid) {
                                r = CMP(y->cpu_fraction, x->cpu_fraction);
                                if (r != 0)
                                        return r;
                        } else if (x->cpu_valid)
                                return -1;
                        else if (y->cpu_valid)
                                return 1;
                } else {
                        r = CMP(y->cpu_usage, x->cpu_usage);
                        if (r != 0)
                                return r;
                }

                break;

        case ORDER_TASKS:
                if (x->n_tasks_valid && y->n_tasks_valid) {
                        r = CMP(y->n_tasks, x->n_tasks);
                        if (r != 0)
                                return r;
                } else if (x->n_tasks_valid)
                        return -1;
                else if (y->n_tasks_valid)
                        return 1;

                break;

        case ORDER_MEMORY:
                if (x->memory_valid && y->memory_valid) {
                        r = CMP(y->memory, x->memory);
                        if (r != 0)
                                return r;
                } else if (x->memory_valid)
                        return -1;
                else if (y->memory_valid)
                        return 1;

                break;

        case ORDER_IO:
                if (x->io_valid && y->io_valid) {
                        r = CMP(y->io_input_bps + y->io_output_bps, x->io_input_bps + x->io_output_bps);
                        if (r != 0)
                                return r;
                } else if (x->io_valid)
                        return -1;
                else if (y->io_valid)
                        return 1;
        }

        return path_compare(x->path, y->path);
}