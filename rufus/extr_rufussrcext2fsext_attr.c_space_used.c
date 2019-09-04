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
struct ext2_xattr {int /*<<< orphan*/  value_len; int /*<<< orphan*/  ea_ino; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ EXT2_EXT_ATTR_LEN (int) ; 
 scalar_t__ EXT2_EXT_ATTR_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_ea_index (int /*<<< orphan*/ ,char const**,int*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int space_used(struct ext2_xattr *attrs, int count)
{
	int total = 0;
	struct ext2_xattr *x;
	const char *shortname;
	int i, len, name_idx;

	for (i = 0, x = attrs; i < count; i++, x++) {
		find_ea_index(x->name, &shortname, &name_idx);
		len = strlen(shortname);
		total += EXT2_EXT_ATTR_LEN(len);
		if (!x->ea_ino)
			total += EXT2_EXT_ATTR_SIZE(x->value_len);
	}
	return total;
}