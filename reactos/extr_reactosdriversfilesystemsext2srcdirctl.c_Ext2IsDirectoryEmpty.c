#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  Inode; } ;
typedef  int /*<<< orphan*/  PEXT2_VCB ;
typedef  TYPE_1__* PEXT2_MCB ;
typedef  int /*<<< orphan*/  PEXT2_IRP_CONTEXT ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  IsMcbDirectory (TYPE_1__*) ; 
 scalar_t__ IsMcbSymLink (TYPE_1__*) ; 
 int TRUE ; 
 int /*<<< orphan*/  ext3_is_dir_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

BOOLEAN
Ext2IsDirectoryEmpty (
    PEXT2_IRP_CONTEXT   IrpContext,
    PEXT2_VCB           Vcb,
    PEXT2_MCB           Mcb
)
{
    if (!IsMcbDirectory(Mcb) || IsMcbSymLink(Mcb)) {
        return TRUE;
    }

    return !!ext3_is_dir_empty(IrpContext, &Mcb->Inode);
}