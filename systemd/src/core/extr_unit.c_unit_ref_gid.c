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
typedef  int /*<<< orphan*/  uid_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_4__ {int /*<<< orphan*/  ref_gid; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  manager_ref_gid ; 
 int unit_ref_uid_internal (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int unit_ref_gid(Unit *u, gid_t gid, bool clean_ipc) {
        return unit_ref_uid_internal(u, (uid_t*) &u->ref_gid, (uid_t) gid, clean_ipc, manager_ref_gid);
}