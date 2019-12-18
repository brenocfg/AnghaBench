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
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CHAR_COLON ; 
 int /*<<< orphan*/  COUNTOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GW_CHILD ; 
 int /*<<< orphan*/  GW_HWNDNEXT ; 
 int /*<<< orphan*/  GetMDIWindowText (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HasDirWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HasTreeWindow (int /*<<< orphan*/ *) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  StripFilespec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hwndMDIClient ; 
 int /*<<< orphan*/  lstrcmpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ *,scalar_t__*) ; 
 int lstrlen (scalar_t__*) ; 

HWND
LocateDirWindow(
    LPTSTR pszPath,
    BOOL bNoFileSpec,
    BOOL bNoTreeWindow)
{
   register HWND hwndT;
   HWND hwndDir;
   LPTSTR pT2;
   TCHAR szTemp[MAXPATHLEN];
   TCHAR szPath[MAXPATHLEN];

   pT2 = pszPath;

   //
   //  Only work with well-formed paths.
   //
   if ((lstrlen(pT2) < 3) || (pT2[1] != CHAR_COLON))
   {
      return (NULL);
   }

   //
   //  Copy path to temp buffer and remove the filespec (if necessary).
   //
   lstrcpy(szPath, pT2);

   if (!bNoFileSpec)
   {
      StripFilespec(szPath);
   }

   //
   //  Cycle through all of the windows until a match is found.
   //
   for (hwndT = GetWindow(hwndMDIClient, GW_CHILD);
        hwndT;
        hwndT = GetWindow(hwndT, GW_HWNDNEXT))
   {
      if (hwndDir = HasDirWindow(hwndT))
      {
         //
         //  Get the Window's path information and remove the file spec.
         //
         GetMDIWindowText(hwndT, szTemp, COUNTOF(szTemp));
         StripFilespec(szTemp);

         //
         //  Compare the two paths.
         //
         if (!lstrcmpi(szTemp, szPath) &&
            (!bNoTreeWindow || !HasTreeWindow(hwndT)))
         {
            break;
         }
      }
   }

   return (hwndT);
}