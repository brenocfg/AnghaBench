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
struct TYPE_3__ {int /*<<< orphan*/  InodeLookasideList; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PEXT2_VCB ;
typedef  int /*<<< orphan*/ * PEXT2_INODE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DL_INF ; 
 int /*<<< orphan*/ * ExAllocateFromNPagedLookasideList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INC_MEM_COUNT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INODE_SIZE ; 
 int /*<<< orphan*/  PS_EXT2_INODE ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

PEXT2_INODE
Ext2AllocateInode (PEXT2_VCB  Vcb)
{
    PVOID inode = NULL;

    inode = ExAllocateFromNPagedLookasideList(
                &(Vcb->InodeLookasideList));
    if (!inode) {
        return NULL;
    }

    RtlZeroMemory(inode, INODE_SIZE);

    DEBUG(DL_INF, ("ExtAllocateInode: Inode created: %ph.\n", inode));
    INC_MEM_COUNT(PS_EXT2_INODE, inode, INODE_SIZE);

    return inode;
}