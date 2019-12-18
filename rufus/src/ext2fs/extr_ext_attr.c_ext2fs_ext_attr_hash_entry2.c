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
struct ext2_ext_attr_entry {scalar_t__ e_value_inum; } ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  int __u32 ;

/* Variables and functions */
 int VALUE_HASH_SHIFT ; 
 int ext2fs_ext_attr_hash_entry (struct ext2_ext_attr_entry*,void*) ; 
 scalar_t__ read_ea_inode_hash (int /*<<< orphan*/ ,scalar_t__,int*) ; 

errcode_t ext2fs_ext_attr_hash_entry2(ext2_filsys fs,
				      struct ext2_ext_attr_entry *entry,
				      void *data, __u32 *hash)
{
	*hash = ext2fs_ext_attr_hash_entry(entry, data);

	if (entry->e_value_inum) {
		__u32 ea_inode_hash;
		errcode_t retval;

		retval = read_ea_inode_hash(fs, entry->e_value_inum,
					    &ea_inode_hash);
		if (retval)
			return retval;

		*hash = (*hash << VALUE_HASH_SHIFT) ^
			(*hash >> (8*sizeof(*hash) - VALUE_HASH_SHIFT)) ^
			ea_inode_hash;
	}
	return 0;
}