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
typedef  int loff_t ;

/* Variables and functions */
 int MAX_LFS_FILESIZE ; 

loff_t ext3_max_size(int blkbits, int has_huge_files)
{
    loff_t res;
    loff_t upper_limit = MAX_LFS_FILESIZE;

    /* small i_blocks in vfs inode? */
    if (!has_huge_files) {
        /*
         * CONFIG_LBD is not enabled implies the inode
         * i_block represent total blocks in 512 bytes
         * 32 == size of vfs inode i_blocks * 8
         */
        upper_limit = ((loff_t)1 << 32) - 1;

        /* total blocks in file system block size */
        upper_limit >>= (blkbits - 9);
        upper_limit <<= blkbits;
    }

    /* 32-bit extent-start container, ee_block */
    res = (loff_t)1 << 32;
    res <<= blkbits;
    res -= 1;

    /* Sanity check against vm- & vfs- imposed limits */
    if (res > upper_limit)
        res = upper_limit;

    return res;
}