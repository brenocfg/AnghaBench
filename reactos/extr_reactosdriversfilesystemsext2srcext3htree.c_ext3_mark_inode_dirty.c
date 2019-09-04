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
struct inode {TYPE_1__* i_sb; } ;
struct ext2_icb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ Ext2SaveInode (struct ext2_icb*,int /*<<< orphan*/ ,struct inode*) ; 

int ext3_mark_inode_dirty(struct ext2_icb *icb, struct inode *in)
{
    if (Ext2SaveInode(icb, in->i_sb->s_priv, in))
        return 0;

    return -ENOMEM;
}