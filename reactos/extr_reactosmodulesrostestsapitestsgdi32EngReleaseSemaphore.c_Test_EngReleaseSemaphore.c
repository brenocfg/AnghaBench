#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ LockCount; scalar_t__ RecursionCount; scalar_t__ OwningThread; scalar_t__ LockSemaphore; scalar_t__ SpinCount; TYPE_1__* DebugInfo; } ;
struct TYPE_3__ {scalar_t__ Type; scalar_t__ CreatorBackTraceIndex; scalar_t__ EntryCount; scalar_t__ ContentionCount; } ;
typedef  TYPE_2__* PRTL_CRITICAL_SECTION ;
typedef  int /*<<< orphan*/ * HSEMAPHORE ;

/* Variables and functions */
 int /*<<< orphan*/  EngAcquireSemaphore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EngCreateSemaphore () ; 
 int /*<<< orphan*/  EngDeleteSemaphore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EngReleaseSemaphore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void Test_EngReleaseSemaphore()
{
    HSEMAPHORE hsem;
    PRTL_CRITICAL_SECTION lpcrit;

    hsem = EngCreateSemaphore();
    ok(hsem != NULL, "EngCreateSemaphore failed\n");
    if (!hsem) return;
    lpcrit = (PRTL_CRITICAL_SECTION)hsem;

    EngAcquireSemaphore(hsem);
    EngReleaseSemaphore(hsem);

    ok(lpcrit->LockCount != 0, "lpcrit->LockCount=%ld\n", lpcrit->LockCount);
    ok(lpcrit->RecursionCount == 0, "lpcrit->RecursionCount=%ld\n", lpcrit->RecursionCount);
    ok(lpcrit->OwningThread == 0, "lpcrit->OwningThread=%p\n", lpcrit->OwningThread);
    ok(lpcrit->LockSemaphore == 0, "lpcrit->LockSemaphore=%p\n", lpcrit->LockSemaphore);
    ok(lpcrit->SpinCount == 0, "lpcrit->SpinCount=%ld\n", lpcrit->SpinCount);

    ok(lpcrit->DebugInfo != NULL, "no DebugInfo\n");
    if (lpcrit->DebugInfo)
    {
        ok(lpcrit->DebugInfo->Type == 0, "DebugInfo->Type=%d\n", lpcrit->DebugInfo->Type);
        ok(lpcrit->DebugInfo->CreatorBackTraceIndex == 0, "DebugInfo->CreatorBackTraceIndex=%d\n", lpcrit->DebugInfo->CreatorBackTraceIndex);
        ok(lpcrit->DebugInfo->EntryCount == 0, "DebugInfo->EntryCount=%ld\n", lpcrit->DebugInfo->EntryCount);
        ok(lpcrit->DebugInfo->ContentionCount == 0, "DebugInfo->ContentionCount=%ld\n", lpcrit->DebugInfo->ContentionCount);
    }

    EngDeleteSemaphore(hsem);
}