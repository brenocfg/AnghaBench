#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ext2_xattr_handle {scalar_t__ count; scalar_t__ capacity; scalar_t__ ino; TYPE_1__* fs; struct ext2_xattr* attrs; } ;
struct ext2_xattr {scalar_t__ ea_ino; unsigned int value_len; scalar_t__ value; scalar_t__ name; } ;
struct ext2_inode_large {scalar_t__ i_generation; } ;
struct ext2_inode {int i_flags; scalar_t__ i_links_count; scalar_t__ i_mtime; scalar_t__ i_generation; } ;
struct ext2_ext_attr_entry {unsigned int e_name_len; scalar_t__ e_value_inum; unsigned int e_value_size; unsigned int e_value_offs; scalar_t__ e_hash; int /*<<< orphan*/  e_name_index; } ;
typedef  int /*<<< orphan*/  ext2_file_t ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  super; } ;

/* Variables and functions */
 scalar_t__ EXT2_ET_BAD_EA_BLOCK_NUM ; 
 scalar_t__ EXT2_ET_BAD_EA_HASH ; 
 scalar_t__ EXT2_ET_EA_BAD_NAME_LEN ; 
 scalar_t__ EXT2_ET_EA_BAD_VALUE_OFFSET ; 
 scalar_t__ EXT2_ET_EA_BAD_VALUE_SIZE ; 
 scalar_t__ EXT2_ET_EA_INODE_CORRUPTED ; 
 struct ext2_ext_attr_entry* EXT2_EXT_ATTR_NEXT (struct ext2_ext_attr_entry*) ; 
 unsigned int EXT2_EXT_ATTR_SIZE (unsigned int) ; 
 int /*<<< orphan*/  EXT2_EXT_IS_LAST_ENTRY (struct ext2_ext_attr_entry*) ; 
 int EXT4_EA_INODE_FL ; 
 int EXT4_INLINE_DATA_FL ; 
 scalar_t__ ext2fs_ext_attr_hash_entry2 (TYPE_1__*,struct ext2_ext_attr_entry*,void*,scalar_t__*) ; 
 int /*<<< orphan*/  ext2fs_file_close (int /*<<< orphan*/ ) ; 
 struct ext2_inode* ext2fs_file_get_inode (int /*<<< orphan*/ ) ; 
 unsigned int ext2fs_file_get_size (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_file_open (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ext2fs_file_read (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_get_mem (unsigned int,scalar_t__*) ; 
 scalar_t__ ext2fs_get_memzero (unsigned int,scalar_t__*) ; 
 int /*<<< orphan*/  ext2fs_has_feature_ea_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ ext2fs_read_inode (TYPE_1__*,scalar_t__,struct ext2_inode*) ; 
 scalar_t__ ext2fs_xattrs_expand (struct ext2_xattr_handle*,int) ; 
 char* find_ea_prefix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,unsigned int) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static errcode_t read_xattrs_from_buffer(struct ext2_xattr_handle *handle,
					 struct ext2_inode_large *inode,
					 struct ext2_ext_attr_entry *entries,
					 unsigned int storage_size,
					 char *value_start)
{
	struct ext2_xattr *x;
	struct ext2_ext_attr_entry *entry, *end;
	const char *prefix;
	unsigned int remain, prefix_len;
	errcode_t err;
	unsigned int values_size = storage_size +
			((char *)entries - value_start);

	/* find the end */
	end = entries;
	remain = storage_size;
	while (remain >= sizeof(struct ext2_ext_attr_entry) &&
	       !EXT2_EXT_IS_LAST_ENTRY(end)) {

		/* header eats this space */
		remain -= sizeof(struct ext2_ext_attr_entry);

		/* is attribute name valid? */
		if (EXT2_EXT_ATTR_SIZE(end->e_name_len) > remain)
			return EXT2_ET_EA_BAD_NAME_LEN;

		/* attribute len eats this space */
		remain -= EXT2_EXT_ATTR_SIZE(end->e_name_len);
		end = EXT2_EXT_ATTR_NEXT(end);
	}

	entry = entries;
	remain = storage_size;
	while (remain >= sizeof(struct ext2_ext_attr_entry) &&
	       !EXT2_EXT_IS_LAST_ENTRY(entry)) {

		/* Allocate space for more attrs? */
		if (handle->count == handle->capacity) {
			err = ext2fs_xattrs_expand(handle, 4);
			if (err)
				return err;
		}

		x = handle->attrs + handle->count;

		/* header eats this space */
		remain -= sizeof(struct ext2_ext_attr_entry);

		/* attribute len eats this space */
		remain -= EXT2_EXT_ATTR_SIZE(entry->e_name_len);

		/* Extract name */
		prefix = find_ea_prefix(entry->e_name_index);
		prefix_len = (prefix ? strlen(prefix) : 0);
		err = ext2fs_get_memzero(entry->e_name_len + prefix_len + 1,
					 &x->name);
		if (err)
			return err;
		if (prefix)
			memcpy(x->name, prefix, prefix_len);
		if (entry->e_name_len)
			memcpy(x->name + prefix_len,
			       (char *)entry + sizeof(*entry),
			       entry->e_name_len);

		/* Check & copy value */
		if (!ext2fs_has_feature_ea_inode(handle->fs->super) &&
		    entry->e_value_inum != 0)
			return EXT2_ET_BAD_EA_BLOCK_NUM;

		if (entry->e_value_inum == 0) {
			if (entry->e_value_size > remain)
				return EXT2_ET_EA_BAD_VALUE_SIZE;

			if (entry->e_value_offs + entry->e_value_size > values_size)
				return EXT2_ET_EA_BAD_VALUE_OFFSET;

			if (entry->e_value_size > 0 &&
			    value_start + entry->e_value_offs <
			    (char *)end + sizeof(__u32))
				return EXT2_ET_EA_BAD_VALUE_OFFSET;

			remain -= entry->e_value_size;

			err = ext2fs_get_mem(entry->e_value_size, &x->value);
			if (err)
				return err;
			memcpy(x->value, value_start + entry->e_value_offs,
			       entry->e_value_size);
		} else {
			struct ext2_inode *ea_inode;
			ext2_file_t ea_file;

			if (entry->e_value_offs != 0)
				return EXT2_ET_EA_BAD_VALUE_OFFSET;

			if (entry->e_value_size > (64 * 1024))
				return EXT2_ET_EA_BAD_VALUE_SIZE;

			err = ext2fs_get_mem(entry->e_value_size, &x->value);
			if (err)
				return err;

			err = ext2fs_file_open(handle->fs, entry->e_value_inum,
					       0, &ea_file);
			if (err)
				return err;

			ea_inode = ext2fs_file_get_inode(ea_file);
			if ((ea_inode->i_flags & EXT4_INLINE_DATA_FL) ||
			    !(ea_inode->i_flags & EXT4_EA_INODE_FL) ||
			    ea_inode->i_links_count == 0)
				err = EXT2_ET_EA_INODE_CORRUPTED;
			else if (ext2fs_file_get_size(ea_file) !=
			    entry->e_value_size)
				err = EXT2_ET_EA_BAD_VALUE_SIZE;
			else
				err = ext2fs_file_read(ea_file, x->value,
						       entry->e_value_size, 0);
			ext2fs_file_close(ea_file);
			if (err)
				return err;
		}

		x->ea_ino = entry->e_value_inum;
		x->value_len = entry->e_value_size;

		/* e_hash may be 0 in older inode's ea */
		if (entry->e_hash != 0) {
			__u32 hash;
			void *data = (entry->e_value_inum != 0) ?
					0 : value_start + entry->e_value_offs;

			err = ext2fs_ext_attr_hash_entry2(handle->fs, entry,
							  data, &hash);
			if (err)
				return err;
			if (entry->e_hash != hash) {
				struct ext2_inode child;

				/* Check whether this is an old Lustre-style
				 * ea_inode reference.
				 */
				err = ext2fs_read_inode(handle->fs,
							entry->e_value_inum,
							&child);
				if (err)
					return err;
				if (child.i_mtime != handle->ino ||
				    child.i_generation != inode->i_generation)
					return EXT2_ET_BAD_EA_HASH;
			}
		}

		handle->count++;
		entry = EXT2_EXT_ATTR_NEXT(entry);
	}

	return 0;
}