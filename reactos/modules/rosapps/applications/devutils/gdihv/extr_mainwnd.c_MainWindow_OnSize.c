#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bottom; int right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_HANDLELIST ; 
 int /*<<< orphan*/  IDC_PROCESSLIST ; 
 int /*<<< orphan*/  IDC_REFRESHHANDLE ; 
 int /*<<< orphan*/  IDC_REFRESHPROCESS ; 
 int /*<<< orphan*/  MoveWindow (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int g_Separator ; 

__attribute__((used)) static LRESULT
MainWindow_OnSize(HWND hMainWnd)
{
	HWND hProcessListctrl, hHandleListCtrl, hProcessRefresh, hHandleRefresh;
	RECT rect;

	hProcessListctrl = GetDlgItem(hMainWnd, IDC_PROCESSLIST);
	hHandleListCtrl = GetDlgItem(hMainWnd, IDC_HANDLELIST);
	hProcessRefresh = GetDlgItem(hMainWnd, IDC_REFRESHPROCESS);
	hHandleRefresh = GetDlgItem(hMainWnd, IDC_REFRESHHANDLE);

	GetClientRect(hMainWnd, &rect);

//g_Separator = (rect.right / 2);
	MoveWindow(hProcessListctrl, 5, 5, g_Separator - 5, rect.bottom - 40, TRUE);
	MoveWindow(hHandleListCtrl, g_Separator + 5, 5, rect.right - g_Separator - 5, rect.bottom - 40, TRUE);
	MoveWindow(hProcessRefresh, g_Separator - 90, rect.bottom - 30, 90, 25, TRUE);
	MoveWindow(hHandleRefresh, rect.right - 90, rect.bottom - 30, 90, 25, TRUE);

	return 0;
}