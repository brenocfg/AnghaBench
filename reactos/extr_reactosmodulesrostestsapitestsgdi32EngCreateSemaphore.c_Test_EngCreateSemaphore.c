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
struct TYPE_4__ {int LockCount; int RecursionCount; int OwningThread; int LockSemaphore; int SpinCount; TYPE_1__* DebugInfo; } ;
struct TYPE_3__ {int Type; int CreatorBackTraceIndex; int EntryCount; int ContentionCount; } ;
typedef  TYPE_2__* PRTL_CRITICAL_SECTION ;
typedef  int /*<<< orphan*/ * HSEMAPHORE ;

/* Variables and functions */
 int /*<<< orphan*/ * EngCreateSemaphore () ; 
 int /*<<< orphan*/  EngDeleteSemaphore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void Test_EngCreateSemaphore()
{
    HSEMAPHORE hsem;
    PRTL_CRITICAL_SECTION lpcrit;

    hsem = EngCreateSemaphore();
    ok(hsem != NULL, "EngCreateSemaphore failed\n");
    if (!hsem) return;
    lpcrit = (PRTL_CRITICAL_SECTION)hsem;

    ok(lpcrit->LockCount == -1, "lpcrit->LockCount=%ld\n", lpcrit->LockCount);
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