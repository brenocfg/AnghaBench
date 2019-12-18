#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_19__ {int QuadPart; int LowPart; scalar_t__ HighPart; } ;
struct TYPE_14__ {int dwFileAttributes; int /*<<< orphan*/  ftLastWriteTime; } ;
struct TYPE_18__ {TYPE_1__ fd; } ;
struct TYPE_15__ {int QuadPart; } ;
struct TYPE_17__ {int dwAttrs; int /*<<< orphan*/  ftLastWriteTime; TYPE_2__ qFileSize; } ;
struct TYPE_16__ {int top; int bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__* LPXDTA ;
typedef  scalar_t__ LPTSTR ;
typedef  int /*<<< orphan*/  LPPOINT ;
typedef  long LPARAM ;
typedef  TYPE_5__ LFNDTA ;
typedef  TYPE_6__ LARGE_INTEGER ;
typedef  int INT ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ATTR_ALL ; 
 int ATTR_ARCHIVE ; 
 int ATTR_COMPRESSED ; 
 int ATTR_DIR ; 
 int ATTR_ENCRYPTED ; 
 int ATTR_HIDDEN ; 
 int ATTR_PARENT ; 
 int ATTR_READONLY ; 
 int ATTR_SYSTEM ; 
 int BS_AUTO3STATE ; 
 int BS_PUSHBUTTON ; 
 int /*<<< orphan*/  CHAR_NULL ; 
 int COUNTOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckAttribsDlgButton (scalar_t__,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ClientToScreen (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateWindowEx (long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__,int,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  EndDialog (scalar_t__,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  FS_CHANGEDISPLAY ; 
 int FS_FILE_COMPRESSION ; 
 int FS_FILE_ENCRYPTION ; 
 int /*<<< orphan*/  FS_GETDIRECTORY ; 
 scalar_t__ FillSimpleVersion (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FillVersionList (scalar_t__) ; 
 int /*<<< orphan*/  FormatError (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int GetCompressedFileSize (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItemText (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ GetSelection (int,int /*<<< orphan*/ *) ; 
 scalar_t__ GetTreeFocus (scalar_t__) ; 
 scalar_t__ GetVersionInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GetVolumeInformation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  GetWindowRect (scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  GetWindowText (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ HasDirWindow (scalar_t__) ; 
 scalar_t__ HasTreeWindow (scalar_t__) ; 
 int /*<<< orphan*/  IDCANCEL ; 
 int /*<<< orphan*/  IDCW_LISTBOX ; 
 int /*<<< orphan*/  IDD_ARCHIVE ; 
 int /*<<< orphan*/  IDD_COMPRESSED ; 
 int /*<<< orphan*/  IDD_CRATIO ; 
 int /*<<< orphan*/  IDD_CRATIOLABEL ; 
 int /*<<< orphan*/  IDD_CSIZE ; 
 int /*<<< orphan*/  IDD_CSIZELABEL ; 
 int /*<<< orphan*/  IDD_DATE ; 
 int /*<<< orphan*/  IDD_DIR ; 
 int /*<<< orphan*/  IDD_ENCRYPTED ; 
 int /*<<< orphan*/  IDD_HELP ; 
 int /*<<< orphan*/  IDD_HIDDEN ; 
 int /*<<< orphan*/  IDD_NAME ; 
 int /*<<< orphan*/  IDD_NAMELABEL ; 
 scalar_t__ IDD_NETWORKFIRST ; 
 int /*<<< orphan*/  IDD_READONLY ; 
 int /*<<< orphan*/  IDD_SIZE ; 
 int /*<<< orphan*/  IDD_SIZELABEL ; 
 int /*<<< orphan*/  IDD_SYSTEM ; 
 int /*<<< orphan*/  IDD_TEXT1 ; 
 int /*<<< orphan*/  IDD_TEXT2 ; 
 int /*<<< orphan*/  IDH_GROUP_ATTRIBS ; 
 int /*<<< orphan*/  IDOK ; 
 int /*<<< orphan*/  IDS_ATTRIBERR ; 
 int /*<<< orphan*/  IDS_DIRNAMELABEL ; 
 int /*<<< orphan*/  LARGE_INTEGER_NULL (TYPE_6__) ; 
 int /*<<< orphan*/  LB_GETCOUNT ; 
 int /*<<< orphan*/  LB_GETSEL ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 scalar_t__ LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 long MAKELPARAM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
 int MB_ICONSTOP ; 
 int MB_OK ; 
 int /*<<< orphan*/ * MemGetFileName (TYPE_4__*) ; 
 int /*<<< orphan*/  MessageBox (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NS_PROPERTYDLG ; 
 int /*<<< orphan*/  OffsetRect (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PostMessage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  PutDate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PutSize (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PutTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SWP_NOMOVE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  ScreenToClient (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SendDlgItemMessage (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int SendMessage (scalar_t__,int /*<<< orphan*/ ,int,long) ; 
 int /*<<< orphan*/  SetDlgItemText (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetWindowDirectory () ; 
 int /*<<< orphan*/  SetWindowLongPtr (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetWindowPos (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SetWindowText (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StripBackslash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StripFilespec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StripPath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WFFindClose (TYPE_5__*) ; 
 int /*<<< orphan*/  WFFindFirst (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WM_GETFONT ; 
 int /*<<< orphan*/  WM_MDIGETACTIVE ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int WNPS_DIR ; 
 int WNPS_FILE ; 
 int WNPS_MULT ; 
 int /*<<< orphan*/  WNTYPE_FILE ; 
 scalar_t__ WN_SUCCESS ; 
 scalar_t__ WNetGetPropertyText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ WNetStat (int /*<<< orphan*/ ) ; 
 int WS_CHILD ; 
 int WS_DISABLED ; 
 int WS_GROUP ; 
 int WS_TABSTOP ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  dwContext ; 
 int /*<<< orphan*/  hAppInstance ; 
 int /*<<< orphan*/  hwndFrame ; 
 scalar_t__ hwndMDIClient ; 
 int /*<<< orphan*/  lstrcat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lstrlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * szMessage ; 
 int /*<<< orphan*/ * szSBytes ; 
 int /*<<< orphan*/ * szTitle ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

INT
InitPropertiesDialog(
   HWND hDlg)
{
   HWND hwndLB, hwndActive, hwndTree;
   LPXDTA lpxdta;
   DWORD dwAttribsOn, dwAttribs3State, dwAttribsLast;
   HWND hwndDir, hwnd, hwndView;
   WCHAR szName[MAXPATHLEN];
   WCHAR szPath[MAXPATHLEN];
   WCHAR szTemp[MAXPATHLEN + 20];
   WCHAR szBuf[MAXPATHLEN];
   WCHAR szNum[MAXPATHLEN];
   INT i, iMac, iCount, dyButton;
   RECT rc, rcT;
   DWORD dwAttrib;
   FILETIME ftLastWrite;
   LFNDTA lfndta;
   LPTSTR p;
   HFONT hFont;
   INT nType = 0;
   DWORD dwFlags;
   BOOL bFileCompression = FALSE;
   BOOL bFileEncryption = FALSE;

   LPTSTR lpszBuf;
   LARGE_INTEGER qSize, qCSize;

   LARGE_INTEGER_NULL(qSize);
   LARGE_INTEGER_NULL(qCSize);

   //
   // this is needed for relative findfirst calls below
   //
   SetWindowDirectory();

   hwndActive = (HWND)SendMessage(hwndMDIClient, WM_MDIGETACTIVE, 0, 0L);
   hwndDir = HasDirWindow(hwndActive);
   hwndTree = HasTreeWindow(hwndActive);

   if (GetVolumeInformation(NULL, NULL, 0L, NULL, NULL, &dwFlags, NULL, 0L))
   {
      bFileCompression = ((dwFlags & FS_FILE_COMPRESSION) == FS_FILE_COMPRESSION);
      bFileEncryption = ((dwFlags & FS_FILE_ENCRYPTION) == FS_FILE_ENCRYPTION);
   }

   iCount = 0;
   dwAttribsOn = 0;                // all bits to check
   dwAttribs3State = 0;            // all bits to 3 state
   dwAttribsLast = 0xFFFF;         // previous bits

   if (hwndTree && hwndTree == GetTreeFocus(hwndActive)) {

      SendMessage(hwndActive, FS_GETDIRECTORY, COUNTOF(szPath), (LPARAM)szPath);
      StripBackslash(szPath);

      if (!WFFindFirst(&lfndta, szPath, ATTR_ALL | ATTR_DIR)) {
         LoadString(hAppInstance, IDS_ATTRIBERR, szMessage, COUNTOF(szMessage));
         FormatError(FALSE, szMessage, COUNTOF(szMessage), ERROR_FILE_NOT_FOUND);

         //
         // BUGBUG: szPath should be set to "Properties for %s"!
         //
         MessageBox(hwndFrame, szMessage, szPath, MB_OK | MB_ICONSTOP);
         EndDialog(hDlg, FALSE);
         return 0;
      }
      WFFindClose(&lfndta);

      dwAttribsOn = lfndta.fd.dwFileAttributes;
      ftLastWrite = lfndta.fd.ftLastWriteTime;

      lstrcpy(szName, szPath);

      goto FullPath;
   }

   if (hwndDir) {
      hwndLB = GetDlgItem(hwndDir, IDCW_LISTBOX);
      hwndView = hwndDir;
   } else {
      hwndLB = GetDlgItem(hwndActive, IDCW_LISTBOX);
      hwndView = hwndActive;
   }

   iMac = SendMessage(hwndLB, LB_GETCOUNT, 0, 0L);

   szPath[0] = CHAR_NULL;
   szName[0] = CHAR_NULL;

   for (i = 0; i < iMac; i++) {

      if (SendMessage(hwndLB, LB_GETSEL, i, 0L)) {

         //
         // get info from either dir or search window
         //
         SendMessage(hwndLB, LB_GETTEXT, i, (LPARAM)&lpxdta);
         dwAttrib = lpxdta->dwAttrs;

         //
         // Check that this is not the .. entry
         //
         if (dwAttrib & ATTR_DIR && dwAttrib & ATTR_PARENT)
            continue;

         qSize.QuadPart = qSize.QuadPart + (lpxdta->qFileSize).QuadPart;

         if (!szName[0]) {

            ftLastWrite = lpxdta->ftLastWriteTime;
            lstrcpy(szName, MemGetFileName(lpxdta));
         }

         dwAttribsOn |= dwAttrib;

         if (dwAttribsLast == 0xFFFF) {

            //
            // save the previous bits for future compares
            //
            dwAttribsLast = dwAttrib;

         } else {

            //
            // remember all bits that don't compare to last bits
            //
            dwAttribs3State |= (dwAttrib ^ dwAttribsLast);
         }

         iCount++;
      }
   }

   GetDlgItemText(hDlg, IDD_TEXT1, szTemp, COUNTOF(szTemp));
   wsprintf(szBuf, szTemp, iCount);
   SetDlgItemText(hDlg, IDD_TEXT1, szBuf);

   GetDlgItemText(hDlg, IDD_TEXT2, szTemp, COUNTOF(szTemp));
   PutSize(&qSize, szNum);
   wsprintf(szBuf, szTemp, szNum);
   SetDlgItemText(hDlg, IDD_TEXT2, szBuf);

   if (iCount == 1)
   {
      if (hwndDir)
      {
         SendMessage(hwndDir, FS_GETDIRECTORY, COUNTOF(szPath), (LPARAM)szPath);
      }
      else
      {
         lstrcpy(szPath, szName);
FullPath:
         StripPath(szName);
         StripFilespec(szPath);
      }

      StripBackslash(szPath);

      GetWindowText(hDlg, szTitle, COUNTOF(szTitle));
      wsprintf(szTemp, szTitle, szName);
      SetWindowText(hDlg, szTemp);

      SetDlgItemText(hDlg, IDD_NAME, szName);
      SetDlgItemText(hDlg, IDD_DIR, szPath);

      if (dwAttribsOn & ATTR_DIR)
      {
         //
         //  Hide size, ratio, and version info.
         //
         if (LoadString(hAppInstance, IDS_DIRNAMELABEL, szTemp, COUNTOF(szTemp)))
            SetDlgItemText(hDlg, IDD_NAMELABEL, szTemp);

         ShowWindow(GetDlgItem(hDlg, IDD_SIZELABEL), SW_HIDE);
         ShowWindow(GetDlgItem(hDlg, IDD_SIZE), SW_HIDE);

         ShowWindow(GetDlgItem(hDlg, IDD_CSIZELABEL), SW_HIDE);
         ShowWindow(GetDlgItem(hDlg, IDD_CSIZE), SW_HIDE);

         ShowWindow(GetDlgItem(hDlg, IDD_CRATIOLABEL), SW_HIDE);
         ShowWindow(GetDlgItem(hDlg, IDD_CRATIO), SW_HIDE);
      }
      else
      {
         if ((bFileCompression) && (dwAttribsOn & ATTR_COMPRESSED))
         {
            qCSize.LowPart = GetCompressedFileSize(szName, &(qCSize.HighPart));
            PutSize(&qCSize, szNum);
            wsprintf(szTemp, szSBytes, szNum);
            SetDlgItemText(hDlg, IDD_CSIZE, szTemp);

            if (qSize.QuadPart != 0)
            {
               //
               //  Ratio = 100 - ((CompressSize * 100) / FileSize)
               //
               qCSize.QuadPart =
                   (qCSize.QuadPart * 100) /
                   qSize.QuadPart;

               if (qCSize.HighPart || (qCSize.LowPart > 100))
               {
                   //
                   //  Ratio = 100%
                   //
                   qCSize.LowPart = 100;
                   qCSize.HighPart = 0;
               }
               else
               {
                   qCSize.LowPart = 100 - qCSize.LowPart;
               }
            }
            else
            {
               //
               //  Ratio = 0%
               //
               qCSize.LowPart = 0;
               qCSize.HighPart = 0;
            }
            PutSize(&qCSize, szNum);
            wsprintf(szTemp, TEXT("%s%%"), szNum);
            SetDlgItemText(hDlg, IDD_CRATIO, szTemp);
         }
         else
         {
            ShowWindow(GetDlgItem(hDlg, IDD_CSIZELABEL), SW_HIDE);
            ShowWindow(GetDlgItem(hDlg, IDD_CSIZE), SW_HIDE);
            ShowWindow(GetDlgItem(hDlg, IDD_CRATIOLABEL), SW_HIDE);
            ShowWindow(GetDlgItem(hDlg, IDD_CRATIO), SW_HIDE);
         }

         PostMessage(hDlg, FS_CHANGEDISPLAY, 0, 0L);

         // changes szPath
         lpszBuf = GetVersionInfo(szPath, szName);

         if (FillSimpleVersion(hDlg, lpszBuf))
            FillVersionList(hDlg);
      }

      if (!bFileCompression)
      {
         ShowWindow(GetDlgItem(hDlg, IDD_COMPRESSED), SW_HIDE);
      }

      if (!bFileEncryption)
      {
         ShowWindow(GetDlgItem(hDlg, IDD_ENCRYPTED), SW_HIDE);
      }

      PutSize(&qSize, szNum);
      wsprintf(szTemp, szSBytes, szNum);
      SetDlgItemText(hDlg, IDD_SIZE, szTemp);

      PutDate(&ftLastWrite, szTemp);
      lstrcat(szTemp, TEXT("  "));
      PutTime(&ftLastWrite, szTemp + lstrlen(szTemp));

      SetDlgItemText(hDlg, IDD_DATE, szTemp);
   }
   else
   {
      dwContext = IDH_GROUP_ATTRIBS;
      
      if (!bFileCompression)
      {
          ShowWindow(GetDlgItem(hDlg, IDD_COMPRESSED), SW_HIDE);
      }

      if (!bFileEncryption)
      {
          ShowWindow(GetDlgItem(hDlg, IDD_ENCRYPTED), SW_HIDE);
      }
   }

   //
   // add the network specific property buttons
   //
   if (WNetStat(NS_PROPERTYDLG)) {
      GetWindowRect(GetDlgItem(hDlg,IDOK), &rcT);
      GetWindowRect(GetDlgItem(hDlg,IDCANCEL), &rc);
      dyButton = rc.top - rcT.top;

      GetWindowRect(GetDlgItem(hDlg,IDD_HELP), &rc);
      ScreenToClient(hDlg,(LPPOINT)&rc.left);
      ScreenToClient(hDlg,(LPPOINT)&rc.right);

      p = GetSelection(4, NULL);
      if (p) {

         for (i = 0; i < 6; i++) {

            if (iCount > 1)
               nType = WNPS_MULT;
            else if (dwAttribsOn & ATTR_DIR)
               nType = WNPS_DIR;
            else
               nType = WNPS_FILE;

            if (WNetGetPropertyText((WORD)i, (WORD)nType, p, szTemp, 30, WNTYPE_FILE) != WN_SUCCESS)
               break;

            if (!szTemp[0])
               break;

            OffsetRect(&rc,0,dyButton);
            hwnd = CreateWindowEx(0L, TEXT("button"), szTemp,
               WS_VISIBLE|WS_CHILD|WS_TABSTOP|BS_PUSHBUTTON,
               rc.left, rc.top,
               rc.right - rc.left, rc.bottom-rc.top,
               hDlg, (HMENU)(i + IDD_NETWORKFIRST), hAppInstance, NULL);

            if (hwnd) {
               hFont = (HFONT)SendDlgItemMessage(hDlg, IDOK, WM_GETFONT, 0, 0L);
               SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
            }
         }

         LocalFree((HANDLE)p);

         ClientToScreen(hDlg,(LPPOINT)&rc.left);
         ClientToScreen(hDlg,(LPPOINT)&rc.right);
         GetWindowRect(hDlg,&rcT);
         rc.bottom += dyButton;
         if (rcT.bottom <= rc.bottom) {
            SetWindowPos(hDlg,NULL,0,0,rcT.right-rcT.left,
            rc.bottom - rcT.top, SWP_NOMOVE|SWP_NOZORDER);
         }
      }
   }

   //
   // change those that don't need to be 3state to regular
   //
   if (ATTR_READONLY & dwAttribs3State)
   {
      SetWindowLongPtr( GetDlgItem(hDlg, IDD_READONLY),
                     GWL_STYLE,
                     WS_VISIBLE | WS_GROUP | WS_TABSTOP | BS_AUTO3STATE | WS_CHILD );
   }
   if (ATTR_HIDDEN & dwAttribs3State)
   {
      SetWindowLongPtr( GetDlgItem(hDlg, IDD_HIDDEN),
                     GWL_STYLE,
                     WS_VISIBLE | BS_AUTO3STATE | WS_CHILD);
   }
   if (ATTR_ARCHIVE & dwAttribs3State)
   {
      SetWindowLongPtr( GetDlgItem(hDlg, IDD_ARCHIVE),
                     GWL_STYLE,
                     WS_VISIBLE | BS_AUTO3STATE | WS_CHILD);
   }
   if (ATTR_SYSTEM & dwAttribs3State)
   {
      SetWindowLongPtr( GetDlgItem(hDlg, IDD_SYSTEM),
                     GWL_STYLE,
                     WS_VISIBLE | BS_AUTO3STATE | WS_CHILD);
   }
   if (ATTR_COMPRESSED & dwAttribs3State)
   {
      SetWindowLongPtr( GetDlgItem(hDlg, IDD_COMPRESSED),
                     GWL_STYLE,
                     WS_VISIBLE | BS_AUTO3STATE | WS_CHILD);
   }
   if (ATTR_ENCRYPTED & dwAttribs3State)
   {
      SetWindowLongPtr( GetDlgItem(hDlg, IDD_ENCRYPTED),
                     GWL_STYLE,
                     WS_VISIBLE | BS_AUTO3STATE | WS_CHILD | WS_DISABLED);
   }

   CheckAttribsDlgButton(hDlg, IDD_READONLY,   ATTR_READONLY, dwAttribs3State, dwAttribsOn);
   CheckAttribsDlgButton(hDlg, IDD_HIDDEN,     ATTR_HIDDEN, dwAttribs3State, dwAttribsOn);
   CheckAttribsDlgButton(hDlg, IDD_ARCHIVE,    ATTR_ARCHIVE, dwAttribs3State, dwAttribsOn);
   CheckAttribsDlgButton(hDlg, IDD_SYSTEM,     ATTR_SYSTEM, dwAttribs3State, dwAttribsOn);
   CheckAttribsDlgButton(hDlg, IDD_COMPRESSED, ATTR_COMPRESSED, dwAttribs3State, dwAttribsOn);
   CheckAttribsDlgButton(hDlg, IDD_ENCRYPTED,  ATTR_ENCRYPTED, dwAttribs3State, dwAttribsOn);

   return nType;
}