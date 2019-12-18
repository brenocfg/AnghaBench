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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MessageBoxExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wconvert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlpCaption ; 
 int /*<<< orphan*/  wlpText ; 

__attribute__((used)) static __inline int MessageBoxExU(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId)
{
	int ret;
	DWORD err = ERROR_INVALID_DATA;
	wconvert(lpText);
	wconvert(lpCaption);
	ret = MessageBoxExW(hWnd, wlpText, wlpCaption, uType, wLanguageId);
	err = GetLastError();
	wfree(lpText);
	wfree(lpCaption);
	SetLastError(err);
	return ret;
}