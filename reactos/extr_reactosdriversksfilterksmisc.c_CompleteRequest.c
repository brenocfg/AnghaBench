#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {scalar_t__ Status; } ;
struct TYPE_7__ {TYPE_1__ IoStatus; } ;
typedef  TYPE_2__* PIRP ;
typedef  int /*<<< orphan*/  CCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  IoCompleteRequest (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ STATUS_PENDING ; 

VOID
CompleteRequest(
    PIRP Irp,
    CCHAR PriorityBoost)
{
    DPRINT("Completing IRP %p Status %x\n", Irp, Irp->IoStatus.Status);

    ASSERT(Irp->IoStatus.Status != STATUS_PENDING);


    IoCompleteRequest(Irp, PriorityBoost);
}