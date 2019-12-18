#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int bt_elem_size; int (* bt_compar ) (void*,void const*) ;} ;
typedef  TYPE_1__ zfs_btree_t ;
struct TYPE_6__ {int bti_offset; int /*<<< orphan*/  bti_before; } ;
typedef  TYPE_2__ zfs_btree_index_t ;
typedef  void uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int stub1 (void*,void const*) ; 

__attribute__((used)) static void *
zfs_btree_find_in_buf(zfs_btree_t *tree, uint8_t *buf, uint64_t nelems,
    const void *value, zfs_btree_index_t *where)
{
	uint64_t max = nelems;
	uint64_t min = 0;
	while (max > min) {
		uint64_t idx = (min + max) / 2;
		uint8_t *cur = buf + idx * tree->bt_elem_size;
		int comp = tree->bt_compar(cur, value);
		if (comp == -1) {
			min = idx + 1;
		} else if (comp == 1) {
			max = idx;
		} else {
			ASSERT0(comp);
			where->bti_offset = idx;
			where->bti_before = B_FALSE;
			return (cur);
		}
	}

	where->bti_offset = max;
	where->bti_before = B_TRUE;
	return (NULL);
}