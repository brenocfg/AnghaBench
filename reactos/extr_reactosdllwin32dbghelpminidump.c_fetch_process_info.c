#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dump_context {scalar_t__ pid; int num_threads; TYPE_2__* threads; } ;
typedef  int ULONG ;
struct TYPE_8__ {int dwThreadCount; int NextEntryOffset; TYPE_3__* ti; int /*<<< orphan*/  UniqueProcessId; } ;
struct TYPE_5__ {int /*<<< orphan*/  UniqueThread; } ;
struct TYPE_7__ {int /*<<< orphan*/  dwCurrentPriority; int /*<<< orphan*/  dwBasePriority; TYPE_1__ ClientId; } ;
struct TYPE_6__ {int /*<<< orphan*/  curr_prio; int /*<<< orphan*/  prio_class; int /*<<< orphan*/  tid; } ;
typedef  TYPE_4__ SYSTEM_PROCESS_INFORMATION ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HandleToULong (int /*<<< orphan*/ ) ; 
 scalar_t__ HandleToUlong (int /*<<< orphan*/ ) ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 void* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ NtQuerySystemInformation (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_INFO_LENGTH_MISMATCH ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  SystemProcessInformation ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL fetch_process_info(struct dump_context* dc)
{
    ULONG       buf_size = 0x1000;
    NTSTATUS    nts;
    void*       pcs_buffer = NULL;

    if (!(pcs_buffer = HeapAlloc(GetProcessHeap(), 0, buf_size))) return FALSE;
    for (;;)
    {
        nts = NtQuerySystemInformation(SystemProcessInformation,
                                       pcs_buffer, buf_size, NULL);
        if (nts != STATUS_INFO_LENGTH_MISMATCH) break;
        pcs_buffer = HeapReAlloc(GetProcessHeap(), 0, pcs_buffer, buf_size *= 2);
        if (!pcs_buffer) return FALSE;
    }

    if (nts == STATUS_SUCCESS)
    {
        SYSTEM_PROCESS_INFORMATION*     spi = pcs_buffer;
        unsigned                        i;

        for (;;)
        {
            if (HandleToUlong(spi->UniqueProcessId) == dc->pid)
            {
                dc->num_threads = spi->dwThreadCount;
                dc->threads = HeapAlloc(GetProcessHeap(), 0,
                                        dc->num_threads * sizeof(dc->threads[0]));
                if (!dc->threads) goto failed;
                for (i = 0; i < dc->num_threads; i++)
                {
                    dc->threads[i].tid        = HandleToULong(spi->ti[i].ClientId.UniqueThread);
                    dc->threads[i].prio_class = spi->ti[i].dwBasePriority; /* FIXME */
                    dc->threads[i].curr_prio  = spi->ti[i].dwCurrentPriority;
                }
                HeapFree(GetProcessHeap(), 0, pcs_buffer);
                return TRUE;
            }
            if (!spi->NextEntryOffset) break;
            spi = (SYSTEM_PROCESS_INFORMATION*)((char*)spi + spi->NextEntryOffset);
        }
    }
failed:
    HeapFree(GetProcessHeap(), 0, pcs_buffer);
    return FALSE;
}