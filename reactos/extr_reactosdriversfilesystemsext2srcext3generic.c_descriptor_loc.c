#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct ext3_sb_info {unsigned int s_desc_per_block; TYPE_1__* s_es; } ;
typedef  unsigned int ext3_group_t ;
typedef  scalar_t__ ext3_fsblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_first_meta_bg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT3_HAS_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 struct ext3_sb_info* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_FEATURE_INCOMPAT_META_BG ; 
 scalar_t__ ext3_bg_has_super (struct super_block*,unsigned int) ; 
 scalar_t__ ext3_group_first_block_no (struct super_block*,unsigned int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

ext3_fsblk_t descriptor_loc(struct super_block *sb,
                            ext3_fsblk_t logical_sb_block, unsigned int nr)
{
    struct ext3_sb_info *sbi = EXT3_SB(sb);
    ext3_group_t bg, first_meta_bg;
    int has_super = 0;

    first_meta_bg = le32_to_cpu(sbi->s_es->s_first_meta_bg);

    if (!EXT3_HAS_INCOMPAT_FEATURE(sb, EXT4_FEATURE_INCOMPAT_META_BG) ||
            nr < first_meta_bg)
        return logical_sb_block + nr + 1;
    bg = sbi->s_desc_per_block * nr;
    if (ext3_bg_has_super(sb, bg))
        has_super = 1;
    return (has_super + ext3_group_first_block_no(sb, bg));
}