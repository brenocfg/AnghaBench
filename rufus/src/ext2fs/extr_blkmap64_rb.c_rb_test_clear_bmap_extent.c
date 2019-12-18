#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;
struct TYPE_5__ {struct rb_node* rb_node; } ;
struct ext2fs_rb_private {TYPE_3__ root; } ;
struct bmap_rb_extent {scalar_t__ start; scalar_t__ count; } ;
typedef  TYPE_1__* ext2fs_generic_bitmap_64 ;
typedef  scalar_t__ __u64 ;
struct TYPE_4__ {scalar_t__ start; scalar_t__ private; } ;

/* Variables and functions */
 scalar_t__ ext2fs_rb_empty_root (TYPE_3__*) ; 
 struct rb_node* ext2fs_rb_next (struct rb_node*) ; 
 struct bmap_rb_extent* node_to_extent (struct rb_node*) ; 

__attribute__((used)) static int rb_test_clear_bmap_extent(ext2fs_generic_bitmap_64 bitmap,
				     __u64 start, unsigned int len)
{
	struct rb_node *parent = NULL, **n;
	struct rb_node *node, *next;
	struct ext2fs_rb_private *bp;
	struct bmap_rb_extent *ext;
	int retval = 1;

	bp = (struct ext2fs_rb_private *) bitmap->private;
	n = &bp->root.rb_node;
	start -= bitmap->start;

	if (len == 0 || ext2fs_rb_empty_root(&bp->root))
		return 1;

	/*
	 * If we find nothing, we should examine whole extent, but
	 * when we find match, the extent is not clean, thus be return
	 * false.
	 */
	while (*n) {
		parent = *n;
		ext = node_to_extent(parent);
		if (start < ext->start) {
			n = &(*n)->rb_left;
		} else if (start >= (ext->start + ext->count)) {
			n = &(*n)->rb_right;
		} else {
			/*
			 * We found extent int the tree -> extent is not
			 * clean
			 */
			return 0;
		}
	}

	node = parent;
	while (node) {
		next = ext2fs_rb_next(node);
		ext = node_to_extent(node);
		node = next;

		if ((ext->start + ext->count) <= start)
			continue;

		/* No more merging */
		if ((start + len) <= ext->start)
			break;

		retval = 0;
		break;
	}
	return retval;
}