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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int PtrToUlong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShellExecuteW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  display_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL launch_file(HWND hwnd, LPCWSTR cmd, UINT nCmdShow)
{
	HINSTANCE hinst = ShellExecuteW(hwnd, NULL/*operation*/, cmd, NULL/*parameters*/, NULL/*dir*/, nCmdShow);

	if (PtrToUlong(hinst) <= 32) {
		display_error(hwnd, GetLastError());
		return FALSE;
	}

	return TRUE;
}