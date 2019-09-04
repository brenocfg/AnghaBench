#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; } ;
struct TYPE_9__ {int Flags2; } ;
struct TYPE_13__ {TYPE_3__* Vcb; TYPE_4__ inode_item; TYPE_2__ Header; TYPE_1__* subvol; } ;
typedef  TYPE_6__ fcb ;
struct TYPE_12__ {scalar_t__ compress; scalar_t__ compress_force; } ;
struct TYPE_10__ {TYPE_5__ options; } ;
struct TYPE_8__ {scalar_t__ id; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BTRFS_INODE_COMPRESS ; 
 int BTRFS_INODE_NOCOMPRESS ; 
 scalar_t__ BTRFS_ROOT_ROOT ; 
 int /*<<< orphan*/  FALSE ; 
 int FSRTL_FLAG2_IS_PAGING_FILE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static __inline BOOL write_fcb_compressed(fcb* fcb) {
    // make sure we don't accidentally write the cache inodes or pagefile compressed
    if (fcb->subvol->id == BTRFS_ROOT_ROOT || fcb->Header.Flags2 & FSRTL_FLAG2_IS_PAGING_FILE)
        return FALSE;

    if (fcb->Vcb->options.compress_force)
        return TRUE;

    if (fcb->inode_item.flags & BTRFS_INODE_NOCOMPRESS)
        return FALSE;

    if (fcb->inode_item.flags & BTRFS_INODE_COMPRESS || fcb->Vcb->options.compress)
        return TRUE;

    return FALSE;
}