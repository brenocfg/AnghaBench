#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * inode_map; } ;
typedef  int /*<<< orphan*/ * PEXT2_INODE_BITMAP ;
typedef  TYPE_1__* PEXT2_FILESYS ;

/* Variables and functions */
 int /*<<< orphan*/  ext2_free_generic_bitmap (int /*<<< orphan*/ *) ; 

void ext2_free_inode_bitmap(PEXT2_FILESYS Ext2Sys)
{
    PEXT2_INODE_BITMAP bitmap = Ext2Sys->inode_map;
    if (!bitmap)
        return;

    ext2_free_generic_bitmap(bitmap);

    Ext2Sys->inode_map = NULL;
}