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
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DisableVersionCtls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetVersionDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDD_COPYRIGHT ; 
 int /*<<< orphan*/  IDD_VERSION ; 
 int /*<<< orphan*/  SetDlgItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  szLegalCopyright ; 

BOOL
FillSimpleVersion(HWND hDlg, LPTSTR lpszValue)
{
   BOOL bRet = TRUE;

   if (lpszValue != NULL)
      SetDlgItemText(hDlg, IDD_VERSION, lpszValue);
   else {
      DisableVersionCtls(hDlg);
      bRet = FALSE;
   }

   lpszValue = GetVersionDatum(szLegalCopyright);

   if (lpszValue != NULL)
      SetDlgItemText(hDlg, IDD_COPYRIGHT, lpszValue);

   return bRet;
}