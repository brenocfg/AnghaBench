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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECT_UPDATE_PROFILE ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_CONNECTEDDRIVELIST ; 
 int /*<<< orphan*/  ID_OK ; 
 int /*<<< orphan*/  LVNI_SELECTED ; 
 int /*<<< orphan*/  ListView_GetItemText (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ListView_GetNextItem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WNetCancelConnection2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _countof (int /*<<< orphan*/ *) ; 

DWORD DisconnectDriveExit(HWND hDlg)
{
    TCHAR driveLetter[10];
    HRESULT hr;
    HWND hListView = GetDlgItem(hDlg, IDC_CONNECTEDDRIVELIST);
    INT nItem = ListView_GetNextItem(hListView, -1, LVNI_SELECTED);

    if (nItem == -1)
        return 0;

    ListView_GetItemText(hListView, nItem, 0, driveLetter, _countof(driveLetter));
    hr = WNetCancelConnection2(driveLetter, CONNECT_UPDATE_PROFILE, FALSE);

    EndDialog(hDlg, ID_OK);
    return hr;
}