#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_10__ {TYPE_1__* Router; } ;
struct TYPE_9__ {struct TYPE_9__* Flink; } ;
struct TYPE_8__ {scalar_t__ Interface; } ;
typedef  TYPE_2__* PLIST_ENTRY ;
typedef  scalar_t__ PIP_INTERFACE ;
typedef  TYPE_3__* PFIB_ENTRY ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 TYPE_3__* CONTAINING_RECORD (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyFIBE (TYPE_3__*) ; 
 TYPE_2__ FIBListHead ; 
 int /*<<< orphan*/  FIBLock ; 
 int /*<<< orphan*/  FIB_ENTRY ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

VOID RouterRemoveRoutesForInterface(PIP_INTERFACE Interface)
{
    KIRQL OldIrql;
    PLIST_ENTRY CurrentEntry;
    PLIST_ENTRY NextEntry;
    PFIB_ENTRY Current;
    
    TcpipAcquireSpinLock(&FIBLock, &OldIrql);
    
    CurrentEntry = FIBListHead.Flink;
    while (CurrentEntry != &FIBListHead) {
        NextEntry = CurrentEntry->Flink;
        Current = CONTAINING_RECORD(CurrentEntry, FIB_ENTRY, ListEntry);

        if (Interface == Current->Router->Interface)
            DestroyFIBE(Current);

        CurrentEntry = NextEntry;
    }
    
    TcpipReleaseSpinLock(&FIBLock, OldIrql);
}