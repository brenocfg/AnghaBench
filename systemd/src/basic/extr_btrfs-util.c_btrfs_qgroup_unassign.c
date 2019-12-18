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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int qgroup_assign_or_unassign (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int btrfs_qgroup_unassign(int fd, uint64_t child, uint64_t parent) {
        return qgroup_assign_or_unassign(fd, false, child, parent);
}