#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_btree_t ;
typedef  int /*<<< orphan*/  zfs_btree_index_t ;
struct TYPE_7__ {TYPE_2__* vdev_initialize_tree; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  rt_root; } ;
typedef  TYPE_2__ range_tree_t ;
typedef  int /*<<< orphan*/  range_seg_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int,int) ; 
 int VDEV_LABEL_START_SIZE ; 
 int rs_get_end (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int rs_get_start (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int vdev_initialize_write (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_btree_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_btree_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfs_initialize_chunk_size ; 

__attribute__((used)) static int
vdev_initialize_ranges(vdev_t *vd, abd_t *data)
{
	range_tree_t *rt = vd->vdev_initialize_tree;
	zfs_btree_t *bt = &rt->rt_root;
	zfs_btree_index_t where;

	for (range_seg_t *rs = zfs_btree_first(bt, &where); rs != NULL;
	    rs = zfs_btree_next(bt, &where, &where)) {
		uint64_t size = rs_get_end(rs, rt) - rs_get_start(rs, rt);

		/* Split range into legally-sized physical chunks */
		uint64_t writes_required =
		    ((size - 1) / zfs_initialize_chunk_size) + 1;

		for (uint64_t w = 0; w < writes_required; w++) {
			int error;

			error = vdev_initialize_write(vd,
			    VDEV_LABEL_START_SIZE + rs_get_start(rs, rt) +
			    (w * zfs_initialize_chunk_size),
			    MIN(size - (w * zfs_initialize_chunk_size),
			    zfs_initialize_chunk_size), data);
			if (error != 0)
				return (error);
		}
	}
	return (0);
}