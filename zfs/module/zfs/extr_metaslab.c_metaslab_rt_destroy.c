#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_btree_t ;
typedef  int /*<<< orphan*/  range_tree_t ;
struct TYPE_3__ {int /*<<< orphan*/ * mra_bt; } ;
typedef  TYPE_1__ metaslab_rt_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zfs_btree_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
metaslab_rt_destroy(range_tree_t *rt, void *arg)
{
	metaslab_rt_arg_t *mrap = arg;
	zfs_btree_t *size_tree = mrap->mra_bt;

	zfs_btree_destroy(size_tree);
	kmem_free(mrap, sizeof (*mrap));
}