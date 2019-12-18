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
struct statfs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_cgroup_fs (struct statfs const*) ; 
 int /*<<< orphan*/  is_temporary_fs (struct statfs const*) ; 

__attribute__((used)) static bool is_physical_fs(const struct statfs *sfs) {
        return !is_temporary_fs(sfs) && !is_cgroup_fs(sfs);
}