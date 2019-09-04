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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int LPARAM ;
typedef  int LONG ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetForegroundWindow () ; 
 int /*<<< orphan*/  IDC_PS_DISPLAYLIST ; 
 int /*<<< orphan*/  LB_GETCOUNT ; 
 int /*<<< orphan*/  LB_GETCURSEL ; 
 int /*<<< orphan*/  LB_GETITEMDATA ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  LB_INSERTSTRING ; 
 int /*<<< orphan*/  LB_RESETCONTENT ; 
 int /*<<< orphan*/  LB_SETCURSEL ; 
 int /*<<< orphan*/  LB_SETITEMDATA ; 
 int SendMessageW (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SetFocus (scalar_t__) ; 
 int /*<<< orphan*/  WM_SETREDRAW ; 

__attribute__((used)) static void update_display_list(HWND hdlg, UINT src_list_id)
{
    LONG count, i, old_pos;
    WCHAR txt[256];
    LONG item_data;
    HWND display_list = GetDlgItem(hdlg, IDC_PS_DISPLAYLIST);
    HWND list = GetDlgItem(hdlg, src_list_id);

    old_pos = SendMessageW(display_list, LB_GETCURSEL, 0, 0);
    if(old_pos == -1) old_pos = 0;

    SendMessageW(display_list, WM_SETREDRAW, 0, 0);
    SendMessageW(display_list, LB_RESETCONTENT, 0, 0);
    count = SendMessageW(list, LB_GETCOUNT, 0, 0);
    for(i = 0; i < count; i++)
    {
        SendMessageW(list, LB_GETTEXT, i, (LPARAM)txt);
        item_data = SendMessageW(list, LB_GETITEMDATA, i, 0);
        SendMessageW(display_list, LB_INSERTSTRING, i, (LPARAM)txt);
        SendMessageW(display_list, LB_SETITEMDATA, i, item_data);
    }
    SendMessageW(display_list, LB_SETCURSEL, 0, 0);
    SendMessageW(display_list, WM_SETREDRAW, 1, 0);
    if(GetForegroundWindow() == hdlg)
        SetFocus(display_list);
}