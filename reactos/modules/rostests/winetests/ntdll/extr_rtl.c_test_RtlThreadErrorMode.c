#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int HardErrorDisabled; } ;
typedef  int NTSTATUS ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 TYPE_1__* NtCurrentTeb () ; 
 int STATUS_INVALID_PARAMETER_1 ; 
 int STATUS_SUCCESS ; 
 int STATUS_WAIT_1 ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  pIsWow64Process (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pRtlGetThreadErrorMode () ; 
 int pRtlSetThreadErrorMode (int,int*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlThreadErrorMode(void)
{
    DWORD oldmode;
    BOOL is_wow64;
    DWORD mode;
    NTSTATUS status;

    if (!pRtlGetThreadErrorMode || !pRtlSetThreadErrorMode)
    {
        win_skip("RtlGetThreadErrorMode and/or RtlSetThreadErrorMode not available\n");
        return;
    }

    if (!pIsWow64Process || !pIsWow64Process(GetCurrentProcess(), &is_wow64))
        is_wow64 = FALSE;

    oldmode = pRtlGetThreadErrorMode();

    status = pRtlSetThreadErrorMode(0x70, &mode);
    ok(status == STATUS_SUCCESS ||
       status == STATUS_WAIT_1, /* Vista */
       "RtlSetThreadErrorMode failed with error 0x%08x\n", status);
    ok(mode == oldmode,
       "RtlSetThreadErrorMode returned mode 0x%x, expected 0x%x\n",
       mode, oldmode);
    ok(pRtlGetThreadErrorMode() == 0x70,
       "RtlGetThreadErrorMode returned 0x%x, expected 0x%x\n", mode, 0x70);
    if (!is_wow64)
    {
        ok(NtCurrentTeb()->HardErrorDisabled == 0x70,
           "The TEB contains 0x%x, expected 0x%x\n",
           NtCurrentTeb()->HardErrorDisabled, 0x70);
    }

    status = pRtlSetThreadErrorMode(0, &mode);
    ok(status == STATUS_SUCCESS ||
       status == STATUS_WAIT_1, /* Vista */
       "RtlSetThreadErrorMode failed with error 0x%08x\n", status);
    ok(mode == 0x70,
       "RtlSetThreadErrorMode returned mode 0x%x, expected 0x%x\n",
       mode, 0x70);
    ok(pRtlGetThreadErrorMode() == 0,
       "RtlGetThreadErrorMode returned 0x%x, expected 0x%x\n", mode, 0);
    if (!is_wow64)
    {
        ok(NtCurrentTeb()->HardErrorDisabled == 0,
           "The TEB contains 0x%x, expected 0x%x\n",
           NtCurrentTeb()->HardErrorDisabled, 0);
    }

    for (mode = 1; mode; mode <<= 1)
    {
        status = pRtlSetThreadErrorMode(mode, NULL);
        if (mode & 0x70)
            ok(status == STATUS_SUCCESS ||
               status == STATUS_WAIT_1, /* Vista */
               "RtlSetThreadErrorMode(%x,NULL) failed with error 0x%08x\n",
               mode, status);
        else
            ok(status == STATUS_INVALID_PARAMETER_1,
               "RtlSetThreadErrorMode(%x,NULL) returns 0x%08x, "
               "expected STATUS_INVALID_PARAMETER_1\n",
               mode, status);
    }

    pRtlSetThreadErrorMode(oldmode, NULL);
}