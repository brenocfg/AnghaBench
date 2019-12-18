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
struct ext2_xattr {char* name; int value_len; char const* value; scalar_t__ ea_ino; } ;
struct ext2_ext_attr_entry {int e_name_len; int e_name_index; int e_value_size; int e_value_offs; scalar_t__ e_hash; scalar_t__ e_value_inum; } ;
typedef  int /*<<< orphan*/  ext2_filsys ;
typedef  scalar_t__ errcode_t ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 struct ext2_ext_attr_entry* EXT2_EXT_ATTR_NEXT (struct ext2_ext_attr_entry*) ; 
 int EXT2_EXT_ATTR_PAD ; 
 scalar_t__ ext2fs_ext_attr_hash_entry2 (int /*<<< orphan*/ ,struct ext2_ext_attr_entry*,char*,scalar_t__*) ; 
 int find_ea_index (char*,char const**,int*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static errcode_t
write_xattrs_to_buffer(ext2_filsys fs, struct ext2_xattr *attrs, int count,
		       void *entries_start, unsigned int storage_size,
		       unsigned int value_offset_correction, int write_hash)
{
	struct ext2_xattr *x;
	struct ext2_ext_attr_entry *e = entries_start;
	char *end = (char *) entries_start + storage_size;
	const char *shortname;
	unsigned int value_size;
	int idx, ret;
	errcode_t err;

	memset(entries_start, 0, storage_size);
	for (x = attrs; x < attrs + count; x++) {
		/* Calculate index and shortname position */
		shortname = x->name;
		ret = find_ea_index(x->name, &shortname, &idx);

		value_size = ((x->value_len + EXT2_EXT_ATTR_PAD - 1) /
			      EXT2_EXT_ATTR_PAD) * EXT2_EXT_ATTR_PAD;

		/* Fill out e appropriately */
		e->e_name_len = strlen(shortname);
		e->e_name_index = (ret ? idx : 0);

		e->e_value_size = x->value_len;
		e->e_value_inum = x->ea_ino;

		/* Store name */
		memcpy((char *)e + sizeof(*e), shortname, e->e_name_len);
		if (x->ea_ino) {
			e->e_value_offs = 0;
		} else {
			end -= value_size;
			e->e_value_offs = end - (char *) entries_start +
						value_offset_correction;
			memcpy(end, x->value, e->e_value_size);
		}

		if (write_hash || x->ea_ino) {
			err = ext2fs_ext_attr_hash_entry2(fs, e,
							  x->ea_ino ? 0 : end,
							  &e->e_hash);
			if (err)
				return err;
		} else
			e->e_hash = 0;

		e = EXT2_EXT_ATTR_NEXT(e);
		*(__u32 *)e = 0;
	}
	return 0;
}