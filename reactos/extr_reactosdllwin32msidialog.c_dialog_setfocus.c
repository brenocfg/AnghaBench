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
struct TYPE_3__ {int /*<<< orphan*/  hWndFocus; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ msi_dialog ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetNextDlgTabItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void dialog_setfocus( msi_dialog *dialog )
{
    HWND hwnd = dialog->hWndFocus;

    hwnd = GetNextDlgTabItem( dialog->hwnd, hwnd, TRUE);
    hwnd = GetNextDlgTabItem( dialog->hwnd, hwnd, FALSE);
    SetFocus( hwnd );
    dialog->hWndFocus = hwnd;
}