#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_15__ ;
typedef  struct TYPE_19__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tbi ;
struct dump_context {int /*<<< orphan*/  hProcess; TYPE_3__* threads; } ;
typedef  int /*<<< orphan*/  lctx ;
typedef  int /*<<< orphan*/  ep ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_27__ {TYPE_15__* ContextRecord; int /*<<< orphan*/  ContextFlags; } ;
struct TYPE_26__ {TYPE_15__* ExceptionPointers; scalar_t__ ClientPointers; } ;
struct TYPE_21__ {scalar_t__ Rva; scalar_t__ DataSize; } ;
struct TYPE_19__ {TYPE_1__ Memory; scalar_t__ StartOfMemoryRange; } ;
struct TYPE_22__ {scalar_t__ Rva; scalar_t__ DataSize; } ;
struct TYPE_25__ {scalar_t__ SuspendCount; TYPE_11__ Stack; scalar_t__ Teb; int /*<<< orphan*/  Priority; int /*<<< orphan*/  PriorityClass; TYPE_2__ ThreadContext; scalar_t__ ThreadId; } ;
struct TYPE_24__ {scalar_t__ ExitStatus; scalar_t__ TebBaseAddress; } ;
struct TYPE_23__ {scalar_t__ tid; int /*<<< orphan*/  curr_prio; int /*<<< orphan*/  prio_class; } ;
struct TYPE_20__ {TYPE_7__* ContextRecord; } ;
typedef  TYPE_4__ THREAD_BASIC_INFORMATION ;
typedef  TYPE_5__ MINIDUMP_THREAD ;
typedef  TYPE_6__ MINIDUMP_EXCEPTION_INFORMATION ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  TYPE_7__ EXCEPTION_POINTERS ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_7__ CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_FULL ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetCurrentThreadId () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetThreadContext (int /*<<< orphan*/ *,TYPE_7__*) ; 
 scalar_t__ NtQueryInformationThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OpenThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ReadProcessMemory (int /*<<< orphan*/ ,TYPE_15__*,TYPE_7__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResumeThread (int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ STILL_ACTIVE ; 
 scalar_t__ SuspendThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THREAD_ALL_ACCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ThreadBasicInformation ; 
 int /*<<< orphan*/  fetch_thread_stack (struct dump_context*,scalar_t__,TYPE_7__*,TYPE_11__*) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL fetch_thread_info(struct dump_context* dc, int thd_idx,
                              const MINIDUMP_EXCEPTION_INFORMATION* except,
                              MINIDUMP_THREAD* mdThd, CONTEXT* ctx)
{
    DWORD                       tid = dc->threads[thd_idx].tid;
    HANDLE                      hThread;
    THREAD_BASIC_INFORMATION    tbi;

    memset(ctx, 0, sizeof(*ctx));

    mdThd->ThreadId = tid;
    mdThd->SuspendCount = 0;
    mdThd->Teb = 0;
    mdThd->Stack.StartOfMemoryRange = 0;
    mdThd->Stack.Memory.DataSize = 0;
    mdThd->Stack.Memory.Rva = 0;
    mdThd->ThreadContext.DataSize = 0;
    mdThd->ThreadContext.Rva = 0;
    mdThd->PriorityClass = dc->threads[thd_idx].prio_class;
    mdThd->Priority = dc->threads[thd_idx].curr_prio;

    if ((hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, tid)) == NULL)
    {
        FIXME("Couldn't open thread %u (%u)\n", tid, GetLastError());
        return FALSE;
    }
    
    if (NtQueryInformationThread(hThread, ThreadBasicInformation,
                                 &tbi, sizeof(tbi), NULL) == STATUS_SUCCESS)
    {
        mdThd->Teb = (ULONG_PTR)tbi.TebBaseAddress;
        if (tbi.ExitStatus == STILL_ACTIVE)
        {
            if (tid != GetCurrentThreadId() &&
                (mdThd->SuspendCount = SuspendThread(hThread)) != (DWORD)-1)
            {
                ctx->ContextFlags = CONTEXT_FULL;
                if (!GetThreadContext(hThread, ctx))
                    memset(ctx, 0, sizeof(*ctx));

                fetch_thread_stack(dc, tbi.TebBaseAddress, ctx, &mdThd->Stack);
                ResumeThread(hThread);
            }
            else if (tid == GetCurrentThreadId() && except)
            {
                CONTEXT lctx, *pctx;
                mdThd->SuspendCount = 1;
                if (except->ClientPointers)
                {
                    EXCEPTION_POINTERS      ep;

                    ReadProcessMemory(dc->hProcess, except->ExceptionPointers,
                                      &ep, sizeof(ep), NULL);
                    ReadProcessMemory(dc->hProcess, ep.ContextRecord,
                                      &lctx, sizeof(lctx), NULL);
                    pctx = &lctx;
                }
                else pctx = except->ExceptionPointers->ContextRecord;

                *ctx = *pctx;
                fetch_thread_stack(dc, tbi.TebBaseAddress, pctx, &mdThd->Stack);
            }
            else mdThd->SuspendCount = 0;
        }
    }
    CloseHandle(hThread);
    return TRUE;
}