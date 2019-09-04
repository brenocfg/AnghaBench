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
typedef  int /*<<< orphan*/  LPRECT ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int DrawTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wconvert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlpText ; 

__attribute__((used)) static __inline int DrawTextU(HDC hDC, LPCSTR lpText, int nCount, LPRECT lpRect, UINT uFormat)
{
	int ret;
	DWORD err = ERROR_INVALID_DATA;
	wconvert(lpText);
	ret = DrawTextW(hDC, wlpText, nCount, lpRect, uFormat);
	err = GetLastError();
	wfree(lpText);
	SetLastError(err);
	return ret;
}