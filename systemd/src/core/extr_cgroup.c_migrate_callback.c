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
typedef  int /*<<< orphan*/  CGroupMask ;

/* Variables and functions */
 char const* unit_get_realized_cgroup_path (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *migrate_callback(CGroupMask mask, void *userdata) {
        return unit_get_realized_cgroup_path(userdata, mask);
}