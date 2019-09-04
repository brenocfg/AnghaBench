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
struct TYPE_8__ {int cb; int /*<<< orphan*/  lpTitle; int /*<<< orphan*/  lpDesktop; } ;
struct TYPE_7__ {void* lpTitle; void* lpDesktop; } ;
typedef  TYPE_1__ STARTUPINFOW ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_2__* LPSTARTUPINFOA ;
typedef  int /*<<< orphan*/  LPSECURITY_ATTRIBUTES ;
typedef  int /*<<< orphan*/  LPPROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateProcessW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_BAD_LENGTH ; 
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  sfree (void*) ; 
 void* utf8_to_wchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wconvert (char const*) ; 
 int /*<<< orphan*/  wfree (char const*) ; 
 int /*<<< orphan*/  wlpApplicationName ; 
 int /*<<< orphan*/  wlpCommandLine ; 
 int /*<<< orphan*/  wlpCurrentDirectory ; 

__attribute__((used)) static __inline BOOL CreateProcessU(const char* lpApplicationName, const char* lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
									LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags,
									LPVOID lpEnvironment, const char* lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo,
									LPPROCESS_INFORMATION lpProcessInformation)
{
	BOOL ret = FALSE;
	DWORD err = ERROR_INVALID_DATA;
	STARTUPINFOW wStartupInfo;
	wconvert(lpApplicationName);
	wconvert(lpCommandLine);
	wconvert(lpCurrentDirectory);

	// Because we're lazy, we'll assume that the A and W structs inherently have the same size
	// Also prevents the use of STARTUPINFOEX
	if (lpStartupInfo->cb != sizeof(STARTUPINFOW)) {
		err = ERROR_BAD_LENGTH; goto out;
	}
	memcpy(&wStartupInfo, lpStartupInfo, lpStartupInfo->cb);
	wStartupInfo.lpDesktop = utf8_to_wchar(lpStartupInfo->lpDesktop);
	wStartupInfo.lpTitle = utf8_to_wchar(lpStartupInfo->lpTitle);
	ret = CreateProcessW(wlpApplicationName, wlpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles,
		dwCreationFlags, lpEnvironment, wlpCurrentDirectory, &wStartupInfo, lpProcessInformation);
	err = GetLastError();
	sfree(wStartupInfo.lpDesktop);
	sfree(wStartupInfo.lpTitle);
out:
	wfree(lpApplicationName);
	wfree(lpCommandLine);
	wfree(lpCurrentDirectory);
	SetLastError(err);
	return ret;
}