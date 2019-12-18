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
typedef  size_t UINT ;
struct TYPE_2__ {int /*<<< orphan*/  idString; scalar_t__ pszName; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ LPTSTR ;
typedef  long LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 void* CHAR_NULL ; 
 int /*<<< orphan*/  COUNTOF (scalar_t__) ; 
 int /*<<< orphan*/  GET_WM_COMMAND_MPS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDD_VERSION_KEY ; 
 int /*<<< orphan*/  IDS_VN_LANGUAGE ; 
 int /*<<< orphan*/  IDS_VN_LANGUAGES ; 
 int /*<<< orphan*/  LBN_SELCHANGE ; 
 int /*<<< orphan*/  LB_ADDSTRING ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_SETCURSEL ; 
 int /*<<< orphan*/  LB_SETITEMDATA ; 
 scalar_t__ LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t MAX_VERNAMES ; 
 int /*<<< orphan*/  PostMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,long) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int VER_KEY_END ; 
 size_t VerLanguageName (int /*<<< orphan*/ ,void**,size_t) ; 
 scalar_t__ VerQueryValueIndexW (int /*<<< orphan*/ ,void**,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WM_COMMAND ; 
 int cXlate ; 
 size_t cchXlateString ; 
 int /*<<< orphan*/  hAppInstance ; 
 int /*<<< orphan*/  lpVersionBuffer ; 
 int /*<<< orphan*/ * lpXlate ; 
 int /*<<< orphan*/  lstrcat (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcmp (scalar_t__,scalar_t__) ; 
 size_t lstrlen (void**) ; 
 void** pszXlate ; 
 scalar_t__ szFileVersion ; 
 scalar_t__ szLegalCopyright ; 
 scalar_t__ szMessage ; 
 void** szVersionKey ; 
 TYPE_1__* vernames ; 

VOID
FillVersionList(HWND hDlg)
{
   LPTSTR lpszKey, lpszValue;

   DWORD cbValue;
   UINT i, j, cchOffset;
   INT idx;
   HWND hwndLB;

   hwndLB = GetDlgItem(hDlg, IDD_VERSION_KEY);

   szVersionKey[VER_KEY_END - 1] = CHAR_NULL;        // strip the backslash

   for (j=0; VerQueryValueIndexW(lpVersionBuffer,
                                szVersionKey,
                                j,
                                (LPVOID*)&lpszKey,
                                (LPVOID*)&lpszValue,
                                &cbValue);  j++) {

      if (!lstrcmp(lpszKey, szFileVersion) ||
          !lstrcmp(lpszKey, szLegalCopyright)) {

          continue;
      }

      for (i=0; i<MAX_VERNAMES; i++)
         if (!lstrcmp(vernames[i].pszName, lpszKey))
            break;

      if (i != MAX_VERNAMES && LoadString(hAppInstance, vernames[i].idString, szMessage, COUNTOF(szMessage)))
         lpszKey=szMessage;

      idx = (INT)SendMessage(hwndLB, LB_ADDSTRING, 0, (LPARAM)lpszKey);

      //
      // Only add if the value len isn't zero.
      // This is checked in the SendMessage 4th parm.
      //
      if (idx != LB_ERR)
         SendMessage(hwndLB, LB_SETITEMDATA, idx, (LPARAM)lpszValue);
   }

   //
   // Now look at the \VarFileInfo\Translations section and add an
   // item for the language(s) this file supports.
   //

   if (lpXlate == NULL || pszXlate == NULL)
      goto Done;

   if (!LoadString(hAppInstance, (cXlate == 1) ? IDS_VN_LANGUAGE : IDS_VN_LANGUAGES,
      szMessage, COUNTOF(szMessage)))

      goto Done;

   idx = SendMessage(hwndLB, LB_ADDSTRING, 0, (LPARAM)szMessage);
   if (idx == LB_ERR)
      goto Done;

   pszXlate[0] = CHAR_NULL;
   cchOffset = 0;
   for (i=0; i<cXlate; i++) {
      if (cchOffset + 2 > cchXlateString)
         break;
      if (i != 0) {
         lstrcat(pszXlate, TEXT(", "));
         cchOffset += 2;
      }

      if (VerLanguageName(lpXlate[i*2],
                          pszXlate+cchOffset,
                          cchXlateString-cchOffset
                          ) > cchXlateString - cchOffset)

         break;

      cchOffset += lstrlen(pszXlate+cchOffset);
   }
   pszXlate[cchXlateString-1] = CHAR_NULL;

   SendMessage(hwndLB, LB_SETITEMDATA, idx, (LPARAM)pszXlate);

Done:

   SendMessage(hwndLB, LB_SETCURSEL, 0, 0L);
   PostMessage(hDlg, WM_COMMAND, GET_WM_COMMAND_MPS(IDD_VERSION_KEY, NULL, LBN_SELCHANGE));
}