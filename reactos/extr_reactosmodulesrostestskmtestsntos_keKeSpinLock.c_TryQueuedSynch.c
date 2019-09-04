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
struct TYPE_3__ {int /*<<< orphan*/  IsAcquired; int /*<<< orphan*/  Irql; int /*<<< orphan*/  QueueNumber; } ;
typedef  int /*<<< orphan*/  PKSPIN_LOCK ;
typedef  TYPE_1__* PCHECK_DATA ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  KeTryToAcquireQueuedSpinLockRaiseToSynch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN TryQueuedSynch(PKSPIN_LOCK SpinLock, PCHECK_DATA CheckData) {
    BOOLEAN Ret = KeTryToAcquireQueuedSpinLockRaiseToSynch(CheckData->QueueNumber, &CheckData->Irql);
    CheckData->IsAcquired = TRUE;
    return Ret;
}