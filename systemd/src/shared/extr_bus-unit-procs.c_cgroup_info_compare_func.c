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
struct CGroupInfo {int /*<<< orphan*/  cgroup_path; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cgroup_info_compare_func(struct CGroupInfo * const *a, struct CGroupInfo * const *b) {
        return strcmp((*a)->cgroup_path, (*b)->cgroup_path);
}