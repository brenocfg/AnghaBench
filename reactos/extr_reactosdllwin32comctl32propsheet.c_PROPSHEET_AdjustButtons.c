#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int y; int x; } ;
struct TYPE_8__ {scalar_t__ hasHelp; scalar_t__ hasApply; } ;
struct TYPE_7__ {int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ PropSheetInfo ;
typedef  TYPE_3__ PADDING_INFO ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DM_SETDEFID ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDCANCEL ; 
 int /*<<< orphan*/  IDC_APPLY_BUTTON ; 
 int /*<<< orphan*/  IDHELP ; 
 int /*<<< orphan*/  IDOK ; 
 TYPE_3__ PROPSHEET_GetPaddingInfo (int /*<<< orphan*/ ) ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOSIZE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL PROPSHEET_AdjustButtons(HWND hwndParent, const PropSheetInfo* psInfo)
{
  HWND hwndButton = GetDlgItem(hwndParent, IDOK);
  RECT rcSheet;
  int x, y;
  int num_buttons = 2;
  int buttonWidth, buttonHeight;
  PADDING_INFO padding = PROPSHEET_GetPaddingInfo(hwndParent);

  if (psInfo->hasApply)
    num_buttons++;

  if (psInfo->hasHelp)
    num_buttons++;

  /*
   * Obtain the size of the buttons.
   */
  GetClientRect(hwndButton, &rcSheet);
  buttonWidth = rcSheet.right;
  buttonHeight = rcSheet.bottom;

  /*
   * Get the size of the property sheet.
   */
  GetClientRect(hwndParent, &rcSheet);

  /*
   * All buttons will be at this y coordinate.
   */
  y = rcSheet.bottom - (padding.y + buttonHeight);

  /*
   * Position OK button and make it default.
   */
  hwndButton = GetDlgItem(hwndParent, IDOK);

  x = rcSheet.right - ((padding.x + buttonWidth) * num_buttons);

  SetWindowPos(hwndButton, 0, x, y, 0, 0,
               SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

  SendMessageW(hwndParent, DM_SETDEFID, IDOK, 0);


  /*
   * Position Cancel button.
   */
  hwndButton = GetDlgItem(hwndParent, IDCANCEL);

  x += padding.x + buttonWidth;

  SetWindowPos(hwndButton, 0, x, y, 0, 0,
               SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

  /*
   * Position Apply button.
   */
  hwndButton = GetDlgItem(hwndParent, IDC_APPLY_BUTTON);

  if(psInfo->hasApply)
    x += padding.x + buttonWidth;
  else
    ShowWindow(hwndButton, SW_HIDE);

  SetWindowPos(hwndButton, 0, x, y, 0, 0,
              SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
  EnableWindow(hwndButton, FALSE);

  /*
   * Position Help button.
   */
  hwndButton = GetDlgItem(hwndParent, IDHELP);

  x += padding.x + buttonWidth;
  SetWindowPos(hwndButton, 0, x, y, 0, 0,
              SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

  if(!psInfo->hasHelp)
    ShowWindow(hwndButton, SW_HIDE);

  return TRUE;
}