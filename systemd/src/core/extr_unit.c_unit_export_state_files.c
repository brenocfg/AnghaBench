#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  manager; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ Unit ;
typedef  int /*<<< orphan*/  ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (int /*<<< orphan*/ ) ; 
 scalar_t__ MANAGER_IS_TEST_RUN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_export_invocation_id (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_export_log_extra_fields (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  unit_export_log_level_max (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  unit_export_log_ratelimit_burst (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  unit_export_log_ratelimit_interval (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * unit_get_exec_context (TYPE_1__*) ; 

void unit_export_state_files(Unit *u) {
        const ExecContext *c;

        assert(u);

        if (!u->id)
                return;

        if (!MANAGER_IS_SYSTEM(u->manager))
                return;

        if (MANAGER_IS_TEST_RUN(u->manager))
                return;

        /* Exports a couple of unit properties to /run/systemd/units/, so that journald can quickly query this data
         * from there. Ideally, journald would use IPC to query this, like everybody else, but that's hard, as long as
         * the IPC system itself and PID 1 also log to the journal.
         *
         * Note that these files really shouldn't be considered API for anyone else, as use a runtime file system as
         * IPC replacement is not compatible with today's world of file system namespaces. However, this doesn't really
         * apply to communication between the journal and systemd, as we assume that these two daemons live in the same
         * namespace at least.
         *
         * Note that some of the "files" exported here are actually symlinks and not regular files. Symlinks work
         * better for storing small bits of data, in particular as we can write them with two system calls, and read
         * them with one. */

        (void) unit_export_invocation_id(u);

        c = unit_get_exec_context(u);
        if (c) {
                (void) unit_export_log_level_max(u, c);
                (void) unit_export_log_extra_fields(u, c);
                (void) unit_export_log_ratelimit_interval(u, c);
                (void) unit_export_log_ratelimit_burst(u, c);
        }
}