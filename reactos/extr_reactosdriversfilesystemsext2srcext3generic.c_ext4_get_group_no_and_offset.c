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
struct ext3_super_block {int /*<<< orphan*/  s_first_data_block; } ;
typedef  scalar_t__ ext4_grpblk_t ;
typedef  scalar_t__ ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_2__ {struct ext3_super_block* s_es; } ;

/* Variables and functions */
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_BLOCKS_PER_GROUP (struct super_block*) ; 
 scalar_t__ do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

void ext4_get_group_no_and_offset(struct super_block *sb, ext4_fsblk_t blocknr,
                                  ext4_group_t *blockgrpp, ext4_grpblk_t *offsetp)
{
    struct ext3_super_block *es = EXT3_SB(sb)->s_es;
    ext4_grpblk_t offset;

    blocknr = blocknr - le32_to_cpu(es->s_first_data_block);
    offset = do_div(blocknr, EXT4_BLOCKS_PER_GROUP(sb));
    if (offsetp)
        *offsetp = offset;
    if (blockgrpp)
        *blockgrpp = (ext4_grpblk_t)blocknr;

}