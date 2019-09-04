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
struct ext4_xattr_item {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_xattr_item_free_data (struct ext4_xattr_item*) ; 
 int /*<<< orphan*/  kfree (struct ext4_xattr_item*) ; 

__attribute__((used)) static void ext4_xattr_item_free(struct ext4_xattr_item *item)
{
	if (item->data)
		ext4_xattr_item_free_data(item);

	kfree(item);
}