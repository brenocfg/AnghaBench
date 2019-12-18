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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 scalar_t__ GetDlgItemTextW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walloc (char*,int) ; 
 scalar_t__ wchar_to_utf8_no_alloc (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wfree (char*) ; 
 int /*<<< orphan*/  wlpString ; 

__attribute__((used)) static __inline UINT GetDlgItemTextU(HWND hDlg, int nIDDlgItem, char* lpString, int nMaxCount)
{
	UINT ret = 0;
	DWORD err = ERROR_INVALID_DATA;
	// coverity[returned_null]
	walloc(lpString, nMaxCount);
	ret = GetDlgItemTextW(hDlg, nIDDlgItem, wlpString, nMaxCount);
	err = GetLastError();
	if ((ret != 0) && ((ret = wchar_to_utf8_no_alloc(wlpString, lpString, nMaxCount)) == 0)) {
		err = GetLastError();
	}
	wfree(lpString);
	SetLastError(err);
	return ret;
}