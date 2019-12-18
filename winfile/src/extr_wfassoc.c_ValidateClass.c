#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {size_t uDesc; int /*<<< orphan*/ * lpszBuf; } ;
typedef  TYPE_1__* PFILETYPE ;
typedef  long LPARAM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDD_CLASSLIST ; 
 int /*<<< orphan*/  IDD_COMMAND ; 
 int /*<<< orphan*/  IDD_CONFIG ; 
 int /*<<< orphan*/  IDD_DELETE ; 
 int /*<<< orphan*/  LB_GETCURSEL ; 
 int /*<<< orphan*/  LB_GETITEMDATA ; 
 int /*<<< orphan*/  LB_SETCURSEL ; 
 scalar_t__ SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,long) ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 scalar_t__ szNone ; 

VOID
ValidateClass(HWND hDlg)
{
   INT i;
   PFILETYPE pFileType;

   //
   // If (none) is selected, we can't config or delete.
   //
   i = (INT)SendDlgItemMessage(hDlg, IDD_CLASSLIST, LB_GETCURSEL, 0, 0L);

   if (-1 == i) {
      SendDlgItemMessage(hDlg, IDD_CLASSLIST, LB_SETCURSEL, 0, 0L);
      i=0;
   }

   EnableWindow(GetDlgItem(hDlg, IDD_CONFIG), i);
   EnableWindow(GetDlgItem(hDlg, IDD_DELETE), i);

   if (i) {

      pFileType = (PFILETYPE) SendDlgItemMessage(hDlg, IDD_CLASSLIST, LB_GETITEMDATA, i, 0L);

      //
      // Put command string there
      //
      SendDlgItemMessage(hDlg, IDD_COMMAND, WM_SETTEXT, 0,
         (LPARAM) &pFileType->lpszBuf[pFileType->uDesc]);

   } else {

      SendDlgItemMessage(hDlg, IDD_COMMAND, WM_SETTEXT, 0, (LPARAM)szNone);
   }
}