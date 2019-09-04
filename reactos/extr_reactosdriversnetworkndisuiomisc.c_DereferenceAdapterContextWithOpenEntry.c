#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {int /*<<< orphan*/  Spinlock; int /*<<< orphan*/  OpenCount; } ;
struct TYPE_8__ {TYPE_1__* FileObject; int /*<<< orphan*/  ListEntry; } ;
struct TYPE_7__ {int /*<<< orphan*/ * FsContext2; int /*<<< orphan*/ * FsContext; } ;
typedef  TYPE_2__* PNDISUIO_OPEN_ENTRY ;
typedef  TYPE_3__* PNDISUIO_ADAPTER_CONTEXT ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePool (TYPE_2__*) ; 
 int /*<<< orphan*/  KeAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 

VOID
DereferenceAdapterContextWithOpenEntry(PNDISUIO_ADAPTER_CONTEXT AdapterContext,
                                       PNDISUIO_OPEN_ENTRY OpenEntry)
{
    KIRQL OldIrql;

    /* Lock the adapter context */
    KeAcquireSpinLock(&AdapterContext->Spinlock, &OldIrql);
    
    /* Decrement the open count */
    AdapterContext->OpenCount--;

    /* Cleanup the open entry if we were given one */
    if (OpenEntry != NULL)
    {
        /* Remove the open entry */
        RemoveEntryList(&OpenEntry->ListEntry);

        /* Invalidate the FO */
        OpenEntry->FileObject->FsContext = NULL;
        OpenEntry->FileObject->FsContext2 = NULL;

        /* Free the open entry */
        ExFreePool(OpenEntry);
    }

    /* Release the adapter context lock */
    KeReleaseSpinLock(&AdapterContext->Spinlock, OldIrql);
}