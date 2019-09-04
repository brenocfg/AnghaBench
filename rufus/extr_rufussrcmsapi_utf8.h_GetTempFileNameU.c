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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_DATA ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetTempFileNameW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  walloc (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ wchar_to_utf8_no_alloc (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wconvert (char*) ; 
 int /*<<< orphan*/  wfree (char*) ; 
 int /*<<< orphan*/  wlpPathName ; 
 int /*<<< orphan*/  wlpPrefixString ; 
 int /*<<< orphan*/  wlpTempFileName ; 

__attribute__((used)) static __inline DWORD GetTempFileNameU(char* lpPathName, char* lpPrefixString, UINT uUnique, char* lpTempFileName)
{
	DWORD ret = 0, err = ERROR_INVALID_DATA;
	wconvert(lpPathName);
	wconvert(lpPrefixString);
	// coverity[returned_null]
	walloc(lpTempFileName, MAX_PATH);
	ret = GetTempFileNameW(wlpPathName, wlpPrefixString, uUnique, wlpTempFileName);
	err = GetLastError();
	if ((ret != 0) && ((ret = wchar_to_utf8_no_alloc(wlpTempFileName, lpTempFileName, MAX_PATH)) == 0)) {
		err = GetLastError();
	}
	wfree(lpTempFileName);
	wfree(lpPrefixString);
	wfree(lpPathName);
	SetLastError(err);
	return ret;
}