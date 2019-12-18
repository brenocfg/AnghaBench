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
struct TYPE_6__ {int /*<<< orphan*/  Event; int /*<<< orphan*/  Lock; int /*<<< orphan*/  ListHead; } ;
typedef  TYPE_1__ sys_mbox_t ;
struct TYPE_7__ {int /*<<< orphan*/  ListEntry; void* Message; } ;
typedef  TYPE_2__* PLWIP_MESSAGE_CONTAINER ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_2__*) ; 
 TYPE_2__* ExAllocatePool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ExInterlockedInsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  KeSetEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 

void
sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
    PLWIP_MESSAGE_CONTAINER Container;
    
    Container = ExAllocatePool(NonPagedPool, sizeof(*Container));
    ASSERT(Container);
    
    Container->Message = msg;
    
    ExInterlockedInsertTailList(&mbox->ListHead,
                                &Container->ListEntry,
                                &mbox->Lock);
    
    KeSetEvent(&mbox->Event, IO_NO_INCREMENT, FALSE);
}