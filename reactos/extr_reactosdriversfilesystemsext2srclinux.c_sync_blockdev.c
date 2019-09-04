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
struct block_device {int /*<<< orphan*/  bd_priv; } ;
typedef  int /*<<< orphan*/  PEXT2_VCB ;

/* Variables and functions */
 int /*<<< orphan*/  Ext2FlushVolume (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 

int sync_blockdev(struct block_device *bdev)
{
    PEXT2_VCB Vcb = (PEXT2_VCB) bdev->bd_priv;
    Ext2FlushVolume(NULL, Vcb, FALSE);
    return 0;
}