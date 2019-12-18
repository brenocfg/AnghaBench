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
typedef  int /*<<< orphan*/  zfs_btree_t ;
typedef  int /*<<< orphan*/  zfs_btree_core_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  enum bt_shift_shape { ____Placeholder_bt_shift_shape } bt_shift_shape ;

/* Variables and functions */
 int /*<<< orphan*/  BSD_RIGHT ; 
 int /*<<< orphan*/  bt_shift_core (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
bt_shift_core_right(zfs_btree_t *tree, zfs_btree_core_t *node, uint64_t idx,
    uint64_t count, enum bt_shift_shape shape)
{
	bt_shift_core(tree, node, idx, count, 1, shape, BSD_RIGHT);
}