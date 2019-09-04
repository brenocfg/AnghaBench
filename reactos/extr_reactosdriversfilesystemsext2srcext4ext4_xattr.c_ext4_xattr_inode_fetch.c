#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ext4_xattr_ref {int /*<<< orphan*/  ea_size; int /*<<< orphan*/  inode_size_rem; TYPE_2__* OnDiskInode; TYPE_1__* fs; } ;
struct ext4_xattr_item {scalar_t__ name_len; int /*<<< orphan*/  data_size; int /*<<< orphan*/  in_inode; } ;
struct ext4_xattr_ibody_header {int dummy; } ;
struct ext4_xattr_entry {int /*<<< orphan*/  e_value_size; scalar_t__ e_name_len; int /*<<< orphan*/  e_name_index; } ;
struct TYPE_4__ {int i_extra_isize; } ;
struct TYPE_3__ {int InodeSize; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EXT4_GOOD_OLD_INODE_SIZE ; 
 struct ext4_xattr_entry* EXT4_XATTR_IFIRST (struct ext4_xattr_ibody_header*) ; 
 struct ext4_xattr_ibody_header* EXT4_XATTR_IHDR (TYPE_2__*) ; 
 int /*<<< orphan*/  EXT4_XATTR_IS_LAST_ENTRY (struct ext4_xattr_entry*) ; 
 scalar_t__ EXT4_XATTR_LEN (scalar_t__) ; 
 char* EXT4_XATTR_NAME (struct ext4_xattr_entry*) ; 
 struct ext4_xattr_entry* EXT4_XATTR_NEXT (struct ext4_xattr_entry*) ; 
 scalar_t__ EXT4_XATTR_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 void* ext4_xattr_entry_data (struct ext4_xattr_ref*,struct ext4_xattr_entry*,int /*<<< orphan*/ ) ; 
 struct ext4_xattr_item* ext4_xattr_item_alloc (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ ext4_xattr_item_alloc_data (struct ext4_xattr_item*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_xattr_item_free (struct ext4_xattr_item*) ; 
 int /*<<< orphan*/  ext4_xattr_item_insert (struct ext4_xattr_ref*,struct ext4_xattr_item*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_xattr_inode_fetch(struct ext4_xattr_ref *xattr_ref)
{
	void *data;
	size_t size_rem;
	int ret = 0;
	struct ext4_xattr_ibody_header *header = NULL;
	struct ext4_xattr_entry *entry = NULL;
	int inode_size = xattr_ref->fs->InodeSize;

	header = EXT4_XATTR_IHDR(xattr_ref->OnDiskInode);
	entry = EXT4_XATTR_IFIRST(header);

	size_rem = inode_size - EXT4_GOOD_OLD_INODE_SIZE -
		   xattr_ref->OnDiskInode->i_extra_isize;
	for (; size_rem > 0 && !EXT4_XATTR_IS_LAST_ENTRY(entry);
	     entry = EXT4_XATTR_NEXT(entry),
	     size_rem -= EXT4_XATTR_LEN(entry->e_name_len)) {
		struct ext4_xattr_item *item;
		char *e_name = EXT4_XATTR_NAME(entry);

		data = ext4_xattr_entry_data(xattr_ref, entry, TRUE);
		if (!data) {
			ret = -EIO;
			goto Finish;
		}

		item = ext4_xattr_item_alloc(entry->e_name_index, e_name,
					     (size_t)entry->e_name_len);
		if (!item) {
			ret = -ENOMEM;
			goto Finish;
		}
		if (ext4_xattr_item_alloc_data(
			item, data, le32_to_cpu(entry->e_value_size)) != 0) {
			ext4_xattr_item_free(item);
			ret = -ENOMEM;
			goto Finish;
		}
		item->in_inode = TRUE;
		ext4_xattr_item_insert(xattr_ref, item);
		xattr_ref->inode_size_rem -=
			EXT4_XATTR_SIZE(item->data_size) +
			EXT4_XATTR_LEN(item->name_len);
		xattr_ref->ea_size += EXT4_XATTR_SIZE(item->data_size) +
				      EXT4_XATTR_LEN(item->name_len);
	}

Finish:
	return ret;
}