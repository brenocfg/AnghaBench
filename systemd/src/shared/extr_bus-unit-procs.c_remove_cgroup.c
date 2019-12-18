#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct CGroupInfo {TYPE_1__* parent; int /*<<< orphan*/  pids; struct CGroupInfo* cgroup_path; int /*<<< orphan*/  is_const; struct CGroupInfo* children; } ;
struct TYPE_2__ {int /*<<< orphan*/  children; } ;
typedef  struct CGroupInfo Hashmap ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct CGroupInfo*) ; 
 int /*<<< orphan*/  assert (struct CGroupInfo*) ; 
 int /*<<< orphan*/  free (struct CGroupInfo*) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_remove (struct CGroupInfo*,struct CGroupInfo*) ; 
 int /*<<< orphan*/  siblings ; 

__attribute__((used)) static void remove_cgroup(Hashmap *cgroups, struct CGroupInfo *cg) {
        assert(cgroups);
        assert(cg);

        while (cg->children)
                remove_cgroup(cgroups, cg->children);

        hashmap_remove(cgroups, cg->cgroup_path);

        if (!cg->is_const)
                free(cg->cgroup_path);

        hashmap_free(cg->pids);

        if (cg->parent)
                LIST_REMOVE(siblings, cg->parent->children, cg);

        free(cg);
}