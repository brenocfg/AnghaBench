#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * hdeskStartup; TYPE_1__* peProcess; } ;
struct TYPE_11__ {scalar_t__ UniqueProcessId; int /*<<< orphan*/  ImageFileName; } ;
typedef  TYPE_2__* PPROCESSINFO ;
typedef  int /*<<< orphan*/  PEPROCESS ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_2__*) ; 
 scalar_t__ DBG_IS_CHANNEL_ENABLED (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgChUserObj ; 
 int /*<<< orphan*/  DbgUserDumpHandleTable () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IntCleanupCurIconCache (TYPE_2__*) ; 
 TYPE_2__* PsGetProcessWin32Process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE_CH (int /*<<< orphan*/ ,char*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  UserDestroyObjectsForOwner (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  UserObj ; 
 int /*<<< orphan*/  UserProcess ; 
 int /*<<< orphan*/  UserSetProcessWindowStation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_LEVEL ; 
 int /*<<< orphan*/  ZwClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  co_IntGraphicsCheck (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gHandleTable ; 
 scalar_t__ gpidLogon ; 
 TYPE_2__* gppiInputProvider ; 
 TYPE_2__* ppiScrnSaver ; 

NTSTATUS
UserProcessDestroy(PEPROCESS Process)
{
    PPROCESSINFO ppiCurrent = PsGetProcessWin32Process(Process);
    ASSERT(ppiCurrent);

    if (ppiScrnSaver == ppiCurrent)
        ppiScrnSaver = NULL;

    /* Destroy user objects */
    UserDestroyObjectsForOwner(gHandleTable, ppiCurrent);

    TRACE_CH(UserProcess, "Freeing ppi 0x%p\n", ppiCurrent);
#if DBG
    if (DBG_IS_CHANNEL_ENABLED(ppiCurrent, DbgChUserObj, WARN_LEVEL))
    {
        TRACE_CH(UserObj, "Dumping user handles at the end of the process %s (Info %p).\n",
            ppiCurrent->peProcess->ImageFileName, ppiCurrent);
        DbgUserDumpHandleTable();
    }
#endif

    /* Remove it from the list of GUI apps */
    co_IntGraphicsCheck(FALSE);

    /*
     * Deregister logon application automatically
     */
    if (gpidLogon == ppiCurrent->peProcess->UniqueProcessId)
        gpidLogon = 0;

    /* Close the current window station */
    UserSetProcessWindowStation(NULL);

    if (gppiInputProvider == ppiCurrent) gppiInputProvider = NULL;

    if (ppiCurrent->hdeskStartup)
    {
        ZwClose(ppiCurrent->hdeskStartup);
        ppiCurrent->hdeskStartup = NULL;
    }

    /* Clean up the process icon cache */
    IntCleanupCurIconCache(ppiCurrent);

    return STATUS_SUCCESS;
}