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
struct TYPE_3__ {int /*<<< orphan*/  UserBuffer; int /*<<< orphan*/ * MdlAddress; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PIRP ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  HighPagePriority ; 
 int /*<<< orphan*/  MmGetSystemAddressForMdlSafe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NormalPagePriority ; 

PVOID
NtfsGetUserBuffer(PIRP Irp,
                  BOOLEAN Paging)
{
    if (Irp->MdlAddress != NULL)
    {
        return MmGetSystemAddressForMdlSafe(Irp->MdlAddress, (Paging ? HighPagePriority : NormalPagePriority));
    }
    else
    {
        return Irp->UserBuffer;
    }
}