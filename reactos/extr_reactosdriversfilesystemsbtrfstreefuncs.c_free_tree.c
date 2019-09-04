#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* root; } ;
typedef  TYPE_2__ tree ;
struct TYPE_10__ {TYPE_1__* nonpaged; } ;
typedef  TYPE_3__ root ;
struct TYPE_8__ {int /*<<< orphan*/  load_tree_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* free_tree2 (TYPE_2__*) ; 

tree* free_tree(tree* t) {
    tree* ret;
    root* r = t->root;

    ExAcquireResourceExclusiveLite(&r->nonpaged->load_tree_lock, TRUE);

    ret = free_tree2(t);

    ExReleaseResourceLite(&r->nonpaged->load_tree_lock);

    return ret;
}