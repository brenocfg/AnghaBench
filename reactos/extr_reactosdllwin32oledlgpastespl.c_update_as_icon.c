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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ ps_struct_t ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CheckDlgButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_PS_CHANGEICON ; 
 int /*<<< orphan*/  IDC_PS_DISPLAYASICON ; 
 int /*<<< orphan*/  IDC_PS_ICONDISPLAY ; 
 int PSF_CHECKDISPLAYASICON ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_as_icon(HWND hdlg, ps_struct_t *ps_struct)
{
    HWND icon_display = GetDlgItem(hdlg, IDC_PS_ICONDISPLAY);
    HWND display_as_icon = GetDlgItem(hdlg, IDC_PS_DISPLAYASICON);
    HWND change_icon = GetDlgItem(hdlg, IDC_PS_CHANGEICON);

    /* FIXME. No as icon handling */
    ps_struct->flags &= ~PSF_CHECKDISPLAYASICON;

    CheckDlgButton(hdlg, IDC_PS_DISPLAYASICON, ps_struct->flags & PSF_CHECKDISPLAYASICON);
    EnableWindow(display_as_icon, 0);
    ShowWindow(icon_display, SW_HIDE);
    EnableWindow(icon_display, 0);
    ShowWindow(change_icon, SW_HIDE);
    EnableWindow(change_icon, 0);
}