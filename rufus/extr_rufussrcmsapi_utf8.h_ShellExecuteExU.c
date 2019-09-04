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
struct TYPE_8__ {int cbSize; int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hInstApp; int /*<<< orphan*/  lpClass; int /*<<< orphan*/  lpDirectory; int /*<<< orphan*/  lpParameters; int /*<<< orphan*/  lpFile; int /*<<< orphan*/  lpVerb; } ;
struct TYPE_7__ {int fMask; int /*<<< orphan*/ * lpClass; int /*<<< orphan*/ * lpDirectory; int /*<<< orphan*/ * lpParameters; int /*<<< orphan*/ * lpFile; int /*<<< orphan*/ * lpVerb; int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hInstApp; } ;
typedef  TYPE_1__ SHELLEXECUTEINFOW ;
typedef  TYPE_2__ SHELLEXECUTEINFOA ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_BAD_LENGTH ; 
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int SEE_MASK_CLASSNAME ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShellExecuteExW (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  sfree (int /*<<< orphan*/ *) ; 
 void* utf8_to_wchar (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline BOOL ShellExecuteExU(SHELLEXECUTEINFOA* lpExecInfo)
{
	BOOL ret = FALSE;
	DWORD err = ERROR_INVALID_DATA;
	SHELLEXECUTEINFOW wExecInfo;

	// Because we're lazy, we'll assume that the A and W structs inherently have the same size
	if (lpExecInfo->cbSize != sizeof(SHELLEXECUTEINFOW)) {
		SetLastError(ERROR_BAD_LENGTH); return FALSE;
	}
	memcpy(&wExecInfo, lpExecInfo, lpExecInfo->cbSize);
	wExecInfo.lpVerb = utf8_to_wchar(lpExecInfo->lpVerb);
	wExecInfo.lpFile = utf8_to_wchar(lpExecInfo->lpFile);
	wExecInfo.lpParameters = utf8_to_wchar(lpExecInfo->lpParameters);
	wExecInfo.lpDirectory = utf8_to_wchar(lpExecInfo->lpDirectory);
	if (wExecInfo.fMask & SEE_MASK_CLASSNAME) {
		wExecInfo.lpClass = utf8_to_wchar(lpExecInfo->lpClass);
	} else {
		wExecInfo.lpClass = NULL;
	}
	ret = ShellExecuteExW(&wExecInfo);
	err = GetLastError();
	// Copy the returned values back
	lpExecInfo->hInstApp = wExecInfo.hInstApp;
	lpExecInfo->hProcess = wExecInfo.hProcess;
	sfree(wExecInfo.lpVerb);
	sfree(wExecInfo.lpFile);
	sfree(wExecInfo.lpParameters);
	sfree(wExecInfo.lpDirectory);
	sfree(wExecInfo.lpClass);
	SetLastError(err);
	return ret;
}