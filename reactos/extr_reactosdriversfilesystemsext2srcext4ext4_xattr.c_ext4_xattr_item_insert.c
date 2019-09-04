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
struct ext4_xattr_ref {int /*<<< orphan*/  ordered_list; int /*<<< orphan*/  root; } ;
struct ext4_xattr_item {int /*<<< orphan*/  list_node; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_xattr_item_cmp ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext4_xattr_item_insert(struct ext4_xattr_ref *xattr_ref,
				   struct ext4_xattr_item *item)
{
	rb_insert(&xattr_ref->root, &item->node,
	      ext4_xattr_item_cmp);
	list_add_tail(&item->list_node, &xattr_ref->ordered_list);
}