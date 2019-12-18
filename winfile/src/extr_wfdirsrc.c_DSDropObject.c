#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {scalar_t__ dwControlData; scalar_t__ hwndSource; scalar_t__ wFmt; scalar_t__ dwData; } ;
struct TYPE_5__ {scalar_t__ dwAttrs; } ;
typedef  scalar_t__ LPXDTALINK ;
typedef  TYPE_1__* LPXDTA ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  TYPE_2__* LPDROPSTRUCT ;
typedef  long LPARAM ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ATTR_DIR ; 
 scalar_t__ ATTR_PARENT ; 
 int /*<<< orphan*/  AddBackslash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHAR_NULL ; 
 int COUNTOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckEsc (int /*<<< orphan*/ *) ; 
 scalar_t__ DMMoveCopyHelper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ DOF_DIRECTORY ; 
 int /*<<< orphan*/  DSRectItem (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ ExecProgram (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ FALSE ; 
 int FSC_REFRESH ; 
 int /*<<< orphan*/  FS_GETDIRECTORY ; 
 int /*<<< orphan*/  FS_GETSELECTION ; 
 int /*<<< orphan*/  GWL_HDTA ; 
 int /*<<< orphan*/  GWL_LISTPARMS ; 
 scalar_t__* GetExtension (int /*<<< orphan*/ *) ; 
 scalar_t__ GetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_EXECERRTITLE ; 
 int /*<<< orphan*/  IDS_EXECMOUSECONFIRM ; 
 int /*<<< orphan*/  IDS_MOUSECONFIRM ; 
 scalar_t__ IDYES ; 
 int /*<<< orphan*/  IsProgramFile (int /*<<< orphan*/ *) ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_GETSEL ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
 int MB_ICONEXCLAMATION ; 
 int MB_OK ; 
 int MB_SYSTEMMODAL ; 
 int MB_YESNO ; 
 int /*<<< orphan*/ * MemGetFileName (TYPE_1__*) ; 
 scalar_t__ MessageBox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MyMessageBox (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SB_SIMPLE ; 
 int /*<<< orphan*/ * SZ_BACKSLASH ; 
 int /*<<< orphan*/ * SZ_DOT ; 
 scalar_t__ SendMessage (scalar_t__,int /*<<< orphan*/ ,int,long) ; 
 int /*<<< orphan*/  SetCurrentDirectory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StripBackslash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StripFilespec (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UpdateWindow (scalar_t__) ; 
 int /*<<< orphan*/  WM_FSC ; 
 int /*<<< orphan*/  WM_MDIGETACTIVE ; 
 scalar_t__ bConfirmMouse ; 
 int /*<<< orphan*/  fShowSourceBitmaps ; 
 int /*<<< orphan*/  hAppInstance ; 
 int /*<<< orphan*/  hwndFrame ; 
 scalar_t__ hwndMDIClient ; 
 scalar_t__ hwndSearch ; 
 scalar_t__ hwndStatus ; 
 int /*<<< orphan*/  iSelHighlight ; 
 int /*<<< orphan*/  lstrcat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lstrlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szMessage ; 
 int /*<<< orphan*/ * szStarDotStar ; 
 int /*<<< orphan*/ * szTitle ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL
DSDropObject(
   HWND hwndHolder,
   HWND hwndLB,
   LPDROPSTRUCT lpds,
   BOOL bSearch)
{
   DWORD      ret;
   LPWSTR     pFrom;
   DWORD      dwAttrib = 0;       // init this to not a dir
   DWORD      dwSelSink;
   LPWSTR     pSel;
   LPWSTR     pSelNoQuote;
   LPXDTA     lpxdta;
   LPXDTALINK lpStart;

   WCHAR szTemp[MAXPATHLEN*2];
   WCHAR szSourceFile[MAXPATHLEN+2];
   WCHAR szSourceFileQualified[MAXPATHLEN+2];

   //
   // Turn off status bar
   //
   SendMessage(hwndStatus, SB_SIMPLE, 0, 0L);
   UpdateWindow(hwndStatus);

   //
   // this is the listbox index of the destination
   //
   dwSelSink = lpds->dwControlData;

   //
   // Are we dropping onto ourselves? (i.e. a selected item in the
   // source listbox OR an unused area of the source listbox)  If
   // so, don't do anything.
   //
   if (hwndHolder == lpds->hwndSource) {
      if ((dwSelSink == (DWORD)-1) || SendMessage(hwndLB, LB_GETSEL, dwSelSink, 0L))
         return TRUE;
   }

   //
   // set the destination, assume move/copy case below (c:\foo\)
   //
   SendMessage(hwndHolder, FS_GETDIRECTORY, COUNTOF(szTemp), (LPARAM)szTemp);

   //
   // Are we dropping on a unused portion of some listbox?
   //
   if (dwSelSink == (DWORD)-1) {
      goto NormalMoveCopy;
   }

   //
   // check for drop on a directory
   //
   lpStart = (LPXDTALINK)GetWindowLongPtr(hwndHolder, GWL_HDTA);

   //
   // If dropping on "No files." or "Access denied." then do normal thing.
   //
   if (!lpStart)
      goto NormalMoveCopy;

   if (SendMessage(hwndLB,
                   LB_GETTEXT,
                   dwSelSink,
                   (LPARAM)&lpxdta) == LB_ERR || !lpxdta) {
      goto NormalMoveCopy;
   }

   lstrcpy(szSourceFile, MemGetFileName(lpxdta));
   dwAttrib = lpxdta->dwAttrs;

   if (dwAttrib & ATTR_DIR) {

      if (bSearch) {

         lstrcpy(szTemp, szSourceFile);

      } else {

         //
         // special case the parent
         //
         if (dwAttrib & ATTR_PARENT) {
            StripBackslash(szTemp);
            StripFilespec(szTemp);
         } else {
            lstrcat(szTemp, szSourceFile);
         }
      }
      goto DirMoveCopy;
   }

   //
   // dropping on a program?
   //
   if (!IsProgramFile(szSourceFile))
      goto NormalMoveCopy;

   //
   // directory drop on a file? this is a NOP
   //
   if (lpds->wFmt == DOF_DIRECTORY) {
      DSRectItem(hwndLB, iSelHighlight, FALSE, FALSE);
      return FALSE;
   }

   //
   // We're dropping a file onto a program.
   // Exec the program using the source file as the parameter.
   //
   // set the directory to that of the program to exec
   //
   SendMessage(hwndHolder, FS_GETDIRECTORY, COUNTOF(szTemp), (LPARAM)szTemp);
   StripBackslash(szTemp);

   SetCurrentDirectory(szTemp);

   //
   // We need a fully qualified version of the exe since SheConvertPath
   // doesn't check the current directory if it finds the exe in the path.
   //
   lstrcpy(szSourceFileQualified, szTemp);
   lstrcat(szSourceFileQualified, SZ_BACKSLASH);
   lstrcat(szSourceFileQualified, szSourceFile);

   //
   // get the selected file
   //
   pSel = (LPWSTR)SendMessage(lpds->hwndSource, FS_GETSELECTION, 1, 0L);
   pSelNoQuote = (LPWSTR)SendMessage(lpds->hwndSource, FS_GETSELECTION, 1|16, 0L);
   if (!pSel || !pSelNoQuote)
   {
      goto DODone;
   }

   if (lstrlen(pSel) > MAXPATHLEN)   // don't blow up below!
      goto DODone;

   //
   // Checkesc on target exe
   //
   CheckEsc(szSourceFile);

   if (bConfirmMouse) {

      LoadString(hAppInstance, IDS_MOUSECONFIRM, szTitle, COUNTOF(szTitle));
      LoadString(hAppInstance, IDS_EXECMOUSECONFIRM, szTemp, COUNTOF(szTemp));

      wsprintf(szMessage, szTemp, szSourceFile, pSel);
      if (MessageBox(hwndFrame, szMessage, szTitle, MB_YESNO | MB_ICONEXCLAMATION) != IDYES)
         goto DODone;
   }


   //
   // create an absolute path to the argument (search window already
   // is absolute)
   //
   if (lpds->hwndSource == hwndSearch) {
      szTemp[0] = CHAR_NULL;
   } else {
      SendMessage(lpds->hwndSource, FS_GETDIRECTORY, COUNTOF(szTemp), (LPARAM)szTemp);
   }

   lstrcat(szTemp, pSelNoQuote);     // this is the parameter to the exec

   //
   // put a "." extension on if none found
   //
   if (*GetExtension(szTemp) == 0)
      lstrcat(szTemp, SZ_DOT);

   //
   // Since it's only 1 filename, checkesc it
   //
   CheckEsc(szTemp);

   ret = ExecProgram(szSourceFileQualified, szTemp, NULL, FALSE, FALSE);

   if (ret)
      MyMessageBox(hwndFrame, IDS_EXECERRTITLE, (WORD)ret, MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);

DODone:
   DSRectItem(hwndLB, iSelHighlight, FALSE, FALSE);
   if (pSel)
   {
      LocalFree((HANDLE)pSel);
   }
   if (pSelNoQuote)
   {
      LocalFree((HANDLE)pSelNoQuote);
   }
   return TRUE;

   // szTemp must not be checkesc'd here.

NormalMoveCopy:
   //
   // Make sure that we don't move into same dir.
   //
   if (GetWindowLongPtr(hwndHolder,
                     GWL_LISTPARMS) == SendMessage(hwndMDIClient,
                                                   WM_MDIGETACTIVE,
                                                   0,
                                                   0L)) {
      return TRUE;
   }

DirMoveCopy:

   //
   // the source filename is in the loword
   //
   pFrom = (LPWSTR)lpds->dwData;

   AddBackslash(szTemp);
   lstrcat(szTemp, szStarDotStar);   // put files in this dir

   //
   // again moved here: target is single!
   //
   CheckEsc(szTemp);

   ret = DMMoveCopyHelper(pFrom, szTemp, fShowSourceBitmaps);

   DSRectItem(hwndLB, iSelHighlight, FALSE, FALSE);

   if (ret)
      return TRUE;

#if 0
   if (!fShowSourceBitmaps)
      SendMessage(lpds->hwndSource, WM_FSC, FSC_REFRESH, 0L);

   //
   // we got dropped on, but if this is a dir we don't need to refresh
   //
   if (!(dwAttrib & ATTR_DIR))
      SendMessage(hwndHolder, WM_FSC, FSC_REFRESH, 0L);
#endif

   return TRUE;
}