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
struct TYPE_5__ {int /*<<< orphan*/  capeff; int /*<<< orphan*/  pid; int /*<<< orphan*/  cmdline; int /*<<< orphan*/  exe; int /*<<< orphan*/  comm; } ;
typedef  TYPE_1__ ClientContext ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free_and_replace (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_process_capeff (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ get_process_cmdline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ get_process_comm (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ get_process_exe (int /*<<< orphan*/ ,char**) ; 
 TYPE_1__* pid_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void client_context_read_basic(ClientContext *c) {
        char *t;

        assert(c);
        assert(pid_is_valid(c->pid));

        if (get_process_comm(c->pid, &t) >= 0)
                free_and_replace(c->comm, t);

        if (get_process_exe(c->pid, &t) >= 0)
                free_and_replace(c->exe, t);

        if (get_process_cmdline(c->pid, SIZE_MAX, 0, &t) >= 0)
                free_and_replace(c->cmdline, t);

        if (get_process_capeff(c->pid, &t) >= 0)
                free_and_replace(c->capeff, t);
}