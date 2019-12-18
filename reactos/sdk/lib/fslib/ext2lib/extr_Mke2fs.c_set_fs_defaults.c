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
struct mke2fs_defaults {int size; int inode_ratio; int blocksize; scalar_t__ type; } ;
struct TYPE_4__ {int s_blocks_count; int /*<<< orphan*/  s_log_block_size; int /*<<< orphan*/  s_log_frag_size; } ;
typedef  TYPE_1__* PEXT2_SUPER_BLOCK ;

/* Variables and functions */
 int EXT2_BLOCK_SIZE (TYPE_1__*) ; 
 int EXT2_MIN_BLOCK_LOG_SIZE ; 
 char const* default_str ; 
 int /*<<< orphan*/  int_log2 (int) ; 
 struct mke2fs_defaults* settings ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

void set_fs_defaults(const char *fs_type,
                PEXT2_SUPER_BLOCK super,
                int blocksize, int *inode_ratio)
{
    int megs;
    int ratio = 0;
    struct mke2fs_defaults *p;

    megs = (super->s_blocks_count * (EXT2_BLOCK_SIZE(super) / 1024) / 1024);

    if (inode_ratio)
        ratio = *inode_ratio;

    if (!fs_type)
        fs_type = default_str;

    for (p = settings; p->type; p++)
    {
        if ((strcmp(p->type, fs_type) != 0) &&
            (strcmp(p->type, default_str) != 0))
            continue;

        if ((p->size != 0) &&
            (megs > p->size))
            continue;

        if (ratio == 0)
            *inode_ratio = p->inode_ratio;

        if (blocksize == 0)
        {
            super->s_log_frag_size = super->s_log_block_size =
                int_log2(p->blocksize >> EXT2_MIN_BLOCK_LOG_SIZE);
        }
    }

    if (blocksize == 0)
    {
        super->s_blocks_count /= EXT2_BLOCK_SIZE(super) / 1024;
    }
}