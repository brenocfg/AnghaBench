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
struct TYPE_4__ {int /*<<< orphan*/  uid_refs; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  clean_ipc_by_uid ; 
 int /*<<< orphan*/  manager_vacuum_uid_refs_internal (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void manager_vacuum_uid_refs(Manager *m) {
        manager_vacuum_uid_refs_internal(m, &m->uid_refs, clean_ipc_by_uid);
}