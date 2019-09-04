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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int CB_ERR ; 
 int /*<<< orphan*/  CB_GETLBTEXT ; 
 int /*<<< orphan*/  CB_GETLBTEXTLEN ; 
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  wchar_to_utf8_no_alloc (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  wfree (char*) ; 

__attribute__((used)) static __inline int ComboBox_GetLBTextU(HWND hCtrl, int index, char* lpString)
{
	int size;
	DWORD err = ERROR_INVALID_DATA;
	wchar_t* wlpString;
	if (lpString == NULL)
		return CB_ERR;
	size = (int)SendMessageW(hCtrl, CB_GETLBTEXTLEN, (WPARAM)index, (LPARAM)0);
	if (size < 0)
		return size;
	wlpString = (wchar_t*)calloc(size+1, sizeof(wchar_t));
	size = (int)SendMessageW(hCtrl, CB_GETLBTEXT, (WPARAM)index, (LPARAM)wlpString);
	err = GetLastError();
	if (size > 0)
		wchar_to_utf8_no_alloc(wlpString, lpString, size+1);
	wfree(lpString);
	SetLastError(err);
	return size;
}