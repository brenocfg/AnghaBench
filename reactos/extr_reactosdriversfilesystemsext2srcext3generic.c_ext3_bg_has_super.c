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
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  ext3_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT3_FEATURE_RO_COMPAT_SPARSE_SUPER ; 
 scalar_t__ EXT3_HAS_RO_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext3_group_sparse (int /*<<< orphan*/ ) ; 

int ext3_bg_has_super(struct super_block *sb, ext3_group_t group)
{
    if (EXT3_HAS_RO_COMPAT_FEATURE(sb,
                                   EXT3_FEATURE_RO_COMPAT_SPARSE_SUPER) &&
            !ext3_group_sparse(group))
        return 0;
    return 1;
}