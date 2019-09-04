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
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_DATA ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetModuleFileNameExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  walloc (char*,scalar_t__) ; 
 scalar_t__ wchar_to_utf8_no_alloc (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  wfree (char*) ; 
 int /*<<< orphan*/  wlpFilename ; 

__attribute__((used)) static __inline DWORD GetModuleFileNameExU(HANDLE hProcess, HMODULE hModule, char* lpFilename, DWORD nSize)
{
	DWORD ret = 0, err = ERROR_INVALID_DATA;
	// coverity[returned_null]
	walloc(lpFilename, nSize);
	ret = GetModuleFileNameExW(hProcess, hModule, wlpFilename, nSize);
	err = GetLastError();
	if ((ret != 0)
		&& ((ret = wchar_to_utf8_no_alloc(wlpFilename, lpFilename, nSize)) == 0)) {
		err = GetLastError();
	}
	wfree(lpFilename);
	SetLastError(err);
	return ret;
}