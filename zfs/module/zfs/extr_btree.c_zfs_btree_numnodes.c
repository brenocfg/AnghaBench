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
struct TYPE_3__ {int /*<<< orphan*/  bt_num_elems; } ;
typedef  TYPE_1__ zfs_btree_t ;
typedef  int /*<<< orphan*/  ulong_t ;

/* Variables and functions */

ulong_t
zfs_btree_numnodes(zfs_btree_t *tree)
{
	return (tree->bt_num_elems);
}