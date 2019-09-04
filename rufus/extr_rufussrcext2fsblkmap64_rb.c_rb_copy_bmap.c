#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct rb_node {struct rb_node* rb_right; } ;
struct TYPE_9__ {struct rb_node* rb_node; } ;
struct ext2fs_rb_private {TYPE_5__ root; int /*<<< orphan*/ * rcursor; } ;
struct bmap_rb_extent {struct rb_node node; } ;
typedef  TYPE_1__* ext2fs_generic_bitmap_64 ;
typedef  scalar_t__ errcode_t ;
struct TYPE_8__ {scalar_t__ private; } ;

/* Variables and functions */
 scalar_t__ ext2fs_get_mem (int,struct bmap_rb_extent**) ; 
 struct rb_node* ext2fs_rb_first (TYPE_5__*) ; 
 int /*<<< orphan*/  ext2fs_rb_insert_color (struct rb_node*,TYPE_5__*) ; 
 struct rb_node* ext2fs_rb_last (TYPE_5__*) ; 
 int /*<<< orphan*/  ext2fs_rb_link_node (struct rb_node*,struct rb_node*,struct rb_node**) ; 
 struct rb_node* ext2fs_rb_next (struct rb_node*) ; 
 int /*<<< orphan*/  memcpy (struct bmap_rb_extent*,struct bmap_rb_extent*,int) ; 
 struct bmap_rb_extent* node_to_extent (struct rb_node*) ; 
 scalar_t__ rb_alloc_private_data (TYPE_1__*) ; 

__attribute__((used)) static errcode_t rb_copy_bmap(ext2fs_generic_bitmap_64 src,
			      ext2fs_generic_bitmap_64 dest)
{
	struct ext2fs_rb_private *src_bp, *dest_bp;
	struct bmap_rb_extent *src_ext, *dest_ext;
	struct rb_node *dest_node, *src_node, *dest_last, **n;
	errcode_t retval = 0;

	retval = rb_alloc_private_data (dest);
	if (retval)
		return retval;

	src_bp = (struct ext2fs_rb_private *) src->private;
	dest_bp = (struct ext2fs_rb_private *) dest->private;
	src_bp->rcursor = NULL;
	dest_bp->rcursor = NULL;

	src_node = ext2fs_rb_first(&src_bp->root);
	while (src_node) {
		src_ext = node_to_extent(src_node);
		retval = ext2fs_get_mem(sizeof (struct bmap_rb_extent),
					&dest_ext);
		if (retval)
			break;

		memcpy(dest_ext, src_ext, sizeof(struct bmap_rb_extent));

		dest_node = &dest_ext->node;
		n = &dest_bp->root.rb_node;

		dest_last = NULL;
		if (*n) {
			dest_last = ext2fs_rb_last(&dest_bp->root);
			n = &(dest_last)->rb_right;
		}

		ext2fs_rb_link_node(dest_node, dest_last, n);
		ext2fs_rb_insert_color(dest_node, &dest_bp->root);

		src_node = ext2fs_rb_next(src_node);
	}

	return retval;
}