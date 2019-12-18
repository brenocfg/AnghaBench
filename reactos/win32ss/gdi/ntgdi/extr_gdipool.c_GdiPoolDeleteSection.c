#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {int /*<<< orphan*/  slhLog; } ;
struct TYPE_8__ {scalar_t__ cAllocCount; int /*<<< orphan*/  pvBaseAddress; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  TYPE_1__* PGDI_POOL_SECTION ;
typedef  TYPE_2__* PGDI_POOL ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_DUMP_EVENT_LIST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  EngFreeMem (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  ZwFreeVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
VOID
GdiPoolDeleteSection(PGDI_POOL pPool, PGDI_POOL_SECTION pSection)
{
    NTSTATUS status;
    SIZE_T cjSize = 0;

    /* Should not have any allocations */
    if (pSection->cAllocCount != 0)
    {
        DPRINT1("There are %lu allocations left, section=%p, pool=%p\n",
                pSection->cAllocCount, pSection, pPool);
        DBG_DUMP_EVENT_LIST(&pPool->slhLog);
        ASSERT(FALSE);
    }

    /* Release the virtual memory */
    status = ZwFreeVirtualMemory(NtCurrentProcess(),
                                 &pSection->pvBaseAddress,
                                 &cjSize,
                                 MEM_RELEASE);
    ASSERT(NT_SUCCESS(status));

    /* Free the section object */
    EngFreeMem(pSection);
}