#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_8__ {int Number; } ;
struct TYPE_7__ {int dwNumberOfProcessors; } ;
typedef  TYPE_1__ SYSTEM_INFO ;
typedef  TYPE_2__ PROCESSOR_POWER_INFORMATION ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_1__*) ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ProcessorInformation ; 
 scalar_t__ STATUS_BUFFER_TOO_SMALL ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pNtPowerInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_query_processor_power_info(void)
{
    NTSTATUS status;
    PROCESSOR_POWER_INFORMATION* ppi;
    ULONG size;
    SYSTEM_INFO si;
    int i;

    GetSystemInfo(&si);
    size = si.dwNumberOfProcessors * sizeof(PROCESSOR_POWER_INFORMATION);
    ppi = HeapAlloc(GetProcessHeap(), 0, size);

    /* If size < (sizeof(PROCESSOR_POWER_INFORMATION) * NumberOfProcessors), Win7 returns
     * STATUS_BUFFER_TOO_SMALL. WinXP returns STATUS_SUCCESS for any value of size.  It copies as
     * many whole PROCESSOR_POWER_INFORMATION structures that there is room for.  Even if there is
     * not enough room for one structure, WinXP still returns STATUS_SUCCESS having done nothing.
     *
     * If ppi == NULL, Win7 returns STATUS_INVALID_PARAMETER while WinXP returns STATUS_SUCCESS
     * and does nothing.
     *
     * The same behavior is seen with CallNtPowerInformation (in powrprof.dll).
     */

    if (si.dwNumberOfProcessors > 1)
    {
        for(i = 0; i < si.dwNumberOfProcessors; i++)
            ppi[i].Number = 0xDEADBEEF;

        /* Call with a buffer size that is large enough to hold at least one but not large
         * enough to hold them all.  This will be STATUS_SUCCESS on WinXP but not on Win7 */
        status = pNtPowerInformation(ProcessorInformation, 0, 0, ppi, size - sizeof(PROCESSOR_POWER_INFORMATION));
        if (status == STATUS_SUCCESS)
        {
            /* lax version found on older Windows like WinXP */
            ok( (ppi[si.dwNumberOfProcessors - 2].Number != 0xDEADBEEF) &&
                (ppi[si.dwNumberOfProcessors - 1].Number == 0xDEADBEEF),
                "Expected all but the last record to be overwritten.\n");

            status = pNtPowerInformation(ProcessorInformation, 0, 0, 0, size);
            ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);

            for(i = 0; i < si.dwNumberOfProcessors; i++)
                ppi[i].Number = 0xDEADBEEF;
            status = pNtPowerInformation(ProcessorInformation, 0, 0, ppi, sizeof(PROCESSOR_POWER_INFORMATION) - 1);
            ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);
            for(i = 0; i < si.dwNumberOfProcessors; i++)
                if (ppi[i].Number != 0xDEADBEEF) break;
            ok( i == si.dwNumberOfProcessors, "Expected untouched buffer\n");
        }
        else
        {
            /* picky version found on newer Windows like Win7 */
            ok( ppi[1].Number == 0xDEADBEEF, "Expected untouched buffer.\n");
            ok( status == STATUS_BUFFER_TOO_SMALL, "Expected STATUS_BUFFER_TOO_SMALL, got %08x\n", status);

            status = pNtPowerInformation(ProcessorInformation, 0, 0, 0, size);
            ok( status == STATUS_SUCCESS || status == STATUS_INVALID_PARAMETER, "Got %08x\n", status);

            status = pNtPowerInformation(ProcessorInformation, 0, 0, ppi, 0);
            ok( status == STATUS_BUFFER_TOO_SMALL || status == STATUS_INVALID_PARAMETER, "Got %08x\n", status);
        }
    }
    else
    {
        skip("Test needs more than one processor.\n");
    }

    status = pNtPowerInformation(ProcessorInformation, 0, 0, ppi, size);
    ok( status == STATUS_SUCCESS, "Expected STATUS_SUCCESS, got %08x\n", status);

    HeapFree(GetProcessHeap(), 0, ppi);
}