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
struct TYPE_3__ {int /*<<< orphan*/  Inode; } ;
typedef  int /*<<< orphan*/  PEXT2_VCB ;
typedef  TYPE_1__* PEXT2_MCB ;

/* Variables and functions */
 int Ext2CheckInodeAccess (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int Ext2CheckFileAccess(PEXT2_VCB Vcb, PEXT2_MCB Mcb, int attempt)
{
    return Ext2CheckInodeAccess(Vcb, &Mcb->Inode, attempt);
}