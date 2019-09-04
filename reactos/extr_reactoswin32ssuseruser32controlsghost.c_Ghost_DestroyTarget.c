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
struct TYPE_3__ {int /*<<< orphan*/ * hwndTarget; } ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_1__ GHOST_DATA ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetWindowThreadProcessId (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ OpenProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCESS_TERMINATE ; 
 int /*<<< orphan*/  TerminateProcess (scalar_t__,int) ; 

__attribute__((used)) static void
Ghost_DestroyTarget(GHOST_DATA *pData)
{
    HWND hwndTarget = pData->hwndTarget;
    DWORD pid;
    HANDLE hProcess;

    pData->hwndTarget = NULL;
    GetWindowThreadProcessId(hwndTarget, &pid);

    hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess)
    {
        TerminateProcess(hProcess, -1);
        CloseHandle(hProcess);
    }

    DestroyWindow(hwndTarget);
}