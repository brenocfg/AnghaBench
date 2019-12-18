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
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetWindowTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walloc (char*,int) ; 
 int wchar_to_utf8_no_alloc (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wfree (char*) ; 
 int /*<<< orphan*/  wlpString ; 

__attribute__((used)) static __inline int GetWindowTextU(HWND hWnd, char* lpString, int nMaxCount)
{
	int ret = 0;
	DWORD err = ERROR_INVALID_DATA;
	// Handle the empty string as GetWindowTextW() returns 0 then
	if ((lpString != NULL) && (nMaxCount > 0))
		lpString[0] = 0;
	// coverity[returned_null]
	walloc(lpString, nMaxCount);
	ret = GetWindowTextW(hWnd, wlpString, nMaxCount);
	err = GetLastError();
	// coverity[var_deref_model]
	if ( (ret != 0) && ((ret = wchar_to_utf8_no_alloc(wlpString, lpString, nMaxCount)) == 0) ) {
		err = GetLastError();
	}
	wfree(lpString);
	SetLastError(err);
	return ret;
}