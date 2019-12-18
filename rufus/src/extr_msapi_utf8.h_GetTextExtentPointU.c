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
typedef  int /*<<< orphan*/  LPSIZE ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetTextExtentPoint32W (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wconvert (char const*) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wfree (char const*) ; 
 int /*<<< orphan*/ * wlpString ; 

__attribute__((used)) static __inline BOOL GetTextExtentPointU(HDC hdc, const char* lpString, LPSIZE lpSize)
{
	BOOL ret = FALSE;
	DWORD err = ERROR_INVALID_DATA;
	wconvert(lpString);
	if (wlpString == NULL)
		return FALSE;
	ret = GetTextExtentPoint32W(hdc, wlpString, (int)wcslen(wlpString), lpSize);
	err = GetLastError();
	wfree(lpString);
	SetLastError(err);
	return ret;
}