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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wconvert (char const*) ; 
 int /*<<< orphan*/  wfree (char const*) ; 
 scalar_t__ wlParam ; 

__attribute__((used)) static __inline LRESULT SendMessageLU(HWND hWnd, UINT Msg, WPARAM wParam, const char* lParam)
{
	LRESULT ret = FALSE;
	DWORD err = ERROR_INVALID_DATA;
	wconvert(lParam);
	ret = SendMessageW(hWnd, Msg, wParam, (LPARAM)wlParam);
	err = GetLastError();
	wfree(lParam);
	SetLastError(err);
	return ret;
}