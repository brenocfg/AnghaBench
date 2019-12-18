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
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
struct TYPE_3__ {size_t HandleTableSize; int /*<<< orphan*/  HandleTableLock; int /*<<< orphan*/ * HandleTable; int /*<<< orphan*/ * ConsoleHandle; } ;
typedef  TYPE_1__* PCONSOLE_PROCESS_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  ConSrvCloseHandleEntry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConsoleFreeHeap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlEnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlLeaveCriticalSection (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VOID
ConSrvFreeHandlesTable(PCONSOLE_PROCESS_DATA ProcessData)
{
    RtlEnterCriticalSection(&ProcessData->HandleTableLock);

    if (ProcessData->HandleTable != NULL)
    {
        ULONG i;

        /*
         * ProcessData->ConsoleHandle is NULL (and the assertion fails) when
         * ConSrvFreeHandlesTable is called in ConSrvConnect during the
         * allocation of a new console.
         */
        // ASSERT(ProcessData->ConsoleHandle);
        if (ProcessData->ConsoleHandle != NULL)
        {
            /* Close all the console handles */
            for (i = 0; i < ProcessData->HandleTableSize; i++)
            {
                ConSrvCloseHandleEntry(&ProcessData->HandleTable[i]);
            }
        }
        /* Free the handles table memory */
        ConsoleFreeHeap(ProcessData->HandleTable);
        ProcessData->HandleTable = NULL;
    }

    ProcessData->HandleTableSize = 0;

    RtlLeaveCriticalSection(&ProcessData->HandleTableLock);
}