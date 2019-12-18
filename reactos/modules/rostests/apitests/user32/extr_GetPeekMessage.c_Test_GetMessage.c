#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MSG ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_ERROR_RCODE_NXRRSET ; 
 scalar_t__ ERROR_INVALID_WINDOW_HANDLE ; 
 scalar_t__ GetLastError () ; 
 int GetMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void Test_GetMessage(HWND hWnd)
{
    MSG msg;

    SetLastError(DNS_ERROR_RCODE_NXRRSET);

    ok(GetMessage(&msg, hWnd, 0, 0) == -1, "\n");
    ok(GetLastError() == ERROR_INVALID_WINDOW_HANDLE, "GetLastError() = %lu\n", GetLastError());
}