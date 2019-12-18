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
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dynamic_user_vacuum (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  exec_runtime_vacuum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manager_vacuum_gid_refs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manager_vacuum_uid_refs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void manager_vacuum(Manager *m) {
        assert(m);

        /* Release any dynamic users no longer referenced */
        dynamic_user_vacuum(m, true);

        /* Release any references to UIDs/GIDs no longer referenced, and destroy any IPC owned by them */
        manager_vacuum_uid_refs(m);
        manager_vacuum_gid_refs(m);

        /* Release any runtimes no longer referenced */
        exec_runtime_vacuum(m);
}