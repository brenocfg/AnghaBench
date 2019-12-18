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
struct TYPE_4__ {int /*<<< orphan*/  ref_gid; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  manager_unref_gid ; 
 int /*<<< orphan*/  unit_unref_uid_internal (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void unit_unref_gid(Unit *u, bool destroy_now) {
        unit_unref_uid_internal(u, (uid_t*) &u->ref_gid, destroy_now, manager_unref_gid);
}