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
struct ext4_xattr_ref {int /*<<< orphan*/  ea_size; int /*<<< orphan*/  block_size_rem; TYPE_1__* fs; TYPE_2__* block_bh; } ;
struct ext4_xattr_item {scalar_t__ name_len; int /*<<< orphan*/  data_size; } ;
struct ext4_xattr_entry {int /*<<< orphan*/  e_value_size; scalar_t__ e_name_len; int /*<<< orphan*/  e_name_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  b_data; } ;
struct TYPE_3__ {size_t BlockSize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOMEM ; 
 struct ext4_xattr_entry* EXT4_XATTR_BFIRST (TYPE_2__*) ; 
 int /*<<< orphan*/  EXT4_XATTR_IS_LAST_ENTRY (struct ext4_xattr_entry*) ; 
 scalar_t__ EXT4_XATTR_LEN (scalar_t__) ; 
 char* EXT4_XATTR_NAME (struct ext4_xattr_entry*) ; 
 struct ext4_xattr_entry* EXT4_XATTR_NEXT (struct ext4_xattr_entry*) ; 
 scalar_t__ EXT4_XATTR_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 void* ext4_xattr_entry_data (struct ext4_xattr_ref*,struct ext4_xattr_entry*,int /*<<< orphan*/ ) ; 
 struct ext4_xattr_item* ext4_xattr_item_alloc (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ ext4_xattr_item_alloc_data (struct ext4_xattr_item*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_xattr_item_free (struct ext4_xattr_item*) ; 
 int /*<<< orphan*/  ext4_xattr_item_insert (struct ext4_xattr_ref*,struct ext4_xattr_item*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_xattr_block_fetch(struct ext4_xattr_ref *xattr_ref)
{
	int ret = 0;
	size_t size_rem;
	void *data;
	struct ext4_xattr_entry *entry = NULL;

	ASSERT(xattr_ref->block_bh->b_data);
	entry = EXT4_XATTR_BFIRST(xattr_ref->block_bh);

	size_rem = xattr_ref->fs->BlockSize;
	for (; size_rem > 0 && !EXT4_XATTR_IS_LAST_ENTRY(entry);
	     entry = EXT4_XATTR_NEXT(entry),
	     size_rem -= EXT4_XATTR_LEN(entry->e_name_len)) {
		struct ext4_xattr_item *item;
		char *e_name = EXT4_XATTR_NAME(entry);

		data = ext4_xattr_entry_data(xattr_ref, entry, FALSE);
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
		ext4_xattr_item_insert(xattr_ref, item);
		xattr_ref->block_size_rem -=
			EXT4_XATTR_SIZE(item->data_size) +
			EXT4_XATTR_LEN(item->name_len);
		xattr_ref->ea_size += EXT4_XATTR_SIZE(item->data_size) +
				      EXT4_XATTR_LEN(item->name_len);
	}

Finish:
	return ret;
}