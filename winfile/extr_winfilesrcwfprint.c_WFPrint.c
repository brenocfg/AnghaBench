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
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetNextFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDD_STATUS ; 
 int /*<<< orphan*/  IDOK ; 
 int /*<<< orphan*/  IDS_PRINTERRTITLE ; 
 int /*<<< orphan*/  IDS_PRINTINGMSG ; 
 scalar_t__ IDS_PRINTONLYONE ; 
 int /*<<< orphan*/  IDS_WINFILE ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
 int MB_ICONEXCLAMATION ; 
 int MB_OK ; 
 int /*<<< orphan*/  MyMessageBox (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ PrintFile (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetDlgItemText (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  hAppInstance ; 
 scalar_t__ hdlgProgress ; 
 scalar_t__ hwndFrame ; 
 int /*<<< orphan*/  szMessage ; 
 int /*<<< orphan*/ * szTitle ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DWORD
WFPrint(LPTSTR pSel)
{
  TCHAR szFile[MAXPATHLEN];
  TCHAR szTemp[MAXPATHLEN];
  DWORD ret;

  /* Turn off the print button. */
  if (hdlgProgress)
      EnableWindow(GetDlgItem(hdlgProgress, IDOK), FALSE);

  if (!(pSel = GetNextFile(pSel, szFile, COUNTOF(szFile))))
      return TRUE;

  /* See if there is more than one file to print.  Abort if so
   */
  if (pSel = GetNextFile(pSel, szTemp, COUNTOF(szTemp))) {
      MyMessageBox(hwndFrame, IDS_WINFILE, IDS_PRINTONLYONE, MB_OK | MB_ICONEXCLAMATION);
      return(FALSE);
  }

  if (hdlgProgress) {
      /* Display the name of the file being printed. */
      LoadString(hAppInstance, IDS_PRINTINGMSG, szTitle, COUNTOF(szTitle));
      wsprintf(szMessage, szTitle, szFile);
      SetDlgItemText(hdlgProgress, IDD_STATUS, szMessage);
  }

  ret = PrintFile(hdlgProgress ? hdlgProgress : hwndFrame, szFile);

  if (ret) {
     MyMessageBox(hwndFrame, IDS_PRINTERRTITLE, ret, MB_OK | MB_ICONEXCLAMATION);
     return FALSE;
  }

  return TRUE;
}