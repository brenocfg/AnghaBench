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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT3_FEATURE_COMPAT_DIR_INDEX ; 
 int /*<<< orphan*/  EXT3_HAS_COMPAT_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* EXT3_I (struct inode*) ; 
 int /*<<< orphan*/  EXT3_INDEX_FL ; 

void ext3_update_dx_flag(struct inode *inode)
{
    if (!EXT3_HAS_COMPAT_FEATURE(inode->i_sb,
                                 EXT3_FEATURE_COMPAT_DIR_INDEX))
        EXT3_I(inode)->i_flags &= ~EXT3_INDEX_FL;
}