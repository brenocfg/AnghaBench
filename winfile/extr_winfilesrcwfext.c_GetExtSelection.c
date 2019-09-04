#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int WPARAM ;
typedef  void* WCHAR ;
typedef  int UINT ;
struct TYPE_11__ {void** szName; int /*<<< orphan*/  dwSize; int /*<<< orphan*/  ftTime; void* bAttr; } ;
struct TYPE_10__ {void** szName; int /*<<< orphan*/  dwSize; int /*<<< orphan*/  ftTime; void* bAttr; } ;
struct TYPE_8__ {int /*<<< orphan*/  LowPart; } ;
struct TYPE_9__ {int dwAttrs; TYPE_1__ qFileSize; int /*<<< orphan*/  ftLastWriteTime; } ;
typedef  scalar_t__ LPXDTALINK ;
typedef  TYPE_2__* LPXDTA ;
typedef  void** LPWSTR ;
typedef  int* LPINT ;
typedef  TYPE_3__* LPFMS_GETFILESELW ;
typedef  TYPE_4__* LPFMS_GETFILESELA ;
typedef  long LPARAM ;
typedef  long LONG ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  void* BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ATTR_LFN ; 
 int ATTR_PARENT ; 
 void* CHAR_NULL ; 
 int COUNTOF (void**) ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FS_GETDIRECTORY ; 
 int /*<<< orphan*/  GWL_HDTA ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetShortPathName (void**,void**,int) ; 
 scalar_t__ GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HasDirWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDCW_LISTBOX ; 
 int /*<<< orphan*/  LB_GETSELCOUNT ; 
 int /*<<< orphan*/  LB_GETSELITEMS ; 
 int /*<<< orphan*/  LB_GETTEXT ; 
 int /*<<< orphan*/  LMEM_FIXED ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int*) ; 
 void** MemGetAlternateFileName (TYPE_2__*) ; 
 void** MemGetFileName (TYPE_2__*) ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,long) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int,void**,int,int /*<<< orphan*/ *,scalar_t__*) ; 
 TYPE_2__** lplpxdtaExtSelItems ; 
 int /*<<< orphan*/  lstrcat (void**,void**) ; 
 int /*<<< orphan*/  lstrcpy (void**,void**) ; 
 void** szExtSelDir ; 
 void** szExtSelDirShort ; 
 int uExtSelItems ; 

LONG
GetExtSelection(
   HWND hwnd,
   UINT uItem,
   LPARAM lParam,
   BOOL bSearch,
   BOOL bGetCount,
   BOOL bLFNAware,
   BOOL bUnicode)
{
#define lpSelW ((LPFMS_GETFILESELW)lParam)
#define lpSelA ((LPFMS_GETFILESELA)lParam)

   LPXDTALINK lpStart;
   LPXDTA lpxdta = NULL;
   UINT uSel, i;
   HWND hwndLB;
   WCHAR szPath[COUNTOF(lpSelW->szName)];
   BOOL bUsedDefaultChar;
   HWND hwndView;
   LPINT  lpExtSelItems;
   LPWSTR pszAlternateFileName;
   LPWSTR pszFileName;

   hwndView = bSearch ?
      hwnd :
      HasDirWindow(hwnd);

   lpStart = (LPXDTALINK)GetWindowLongPtr(hwndView, GWL_HDTA);
   hwndLB = GetDlgItem(hwndView, IDCW_LISTBOX);

   if (uExtSelItems == (UINT)-1) {

      //
      // Cache invalid, refresh
      //
      uExtSelItems = (UINT) SendMessage(hwndLB, LB_GETSELCOUNT, 0, 0L);

      lpExtSelItems = (LPINT) LocalAlloc(LMEM_FIXED, sizeof(INT) * uExtSelItems);

      if (lpExtSelItems == NULL) {
         uExtSelItems = (UINT)-1;
         return 0L;
      }

      lplpxdtaExtSelItems = (LPXDTA*) LocalAlloc(LMEM_FIXED,
                                                 sizeof(LPXDTA) * uExtSelItems);

      if (lplpxdtaExtSelItems == NULL) {

         LocalFree(lpExtSelItems);
         uExtSelItems = (UINT)-1;
         return 0L;
      }

      uExtSelItems = (UINT)SendMessage(hwndLB,
                                       LB_GETSELITEMS,
                                       (WPARAM)uExtSelItems,
                                       (LPARAM)lpExtSelItems);

      for (i=0, uSel=0; i < uExtSelItems; i++) {

         SendMessage(hwndLB,
                     LB_GETTEXT,
                     lpExtSelItems[i],
                     (LPARAM)&lplpxdtaExtSelItems[i]);
      }

      //
      // We can't cache this because there's files may be in many
      // different directories.
      //
      if (!bSearch) {
         SendMessage(hwnd,
                     FS_GETDIRECTORY,
                     COUNTOF(szExtSelDir),
                     (LPARAM)szExtSelDir);

	 GetShortPathName(szExtSelDir, szExtSelDirShort, COUNTOF(szExtSelDirShort));
      }

      LocalFree(lpExtSelItems);
   }


   for (i=0, uSel=0; i < uExtSelItems; i++) {

      lpxdta = lplpxdtaExtSelItems[i];

      if (!lpxdta || lpxdta->dwAttrs & ATTR_PARENT)
         continue;

      if ((!bLFNAware && (lpxdta->dwAttrs & ATTR_LFN)) &&
         !MemGetAlternateFileName(lpxdta)[0]) {

         continue;
      }

      if (!bGetCount && uItem == uSel) {
         break;
      }

      uSel++;
   }

   if (!lpxdta)
   {
       //
       //  Quit out if lpxdta is null.
       //
       return (0L);
   }

   //
   // We use uSel regardless; if we wanted item #4 but we ran out
   // at #2, give'm #2.  This adheres to the previous semantics.
   //
   if (bGetCount) {
      return (LONG)uSel;
   }

   pszAlternateFileName = MemGetAlternateFileName(lpxdta);

   if (bUnicode) {

      //
      // lpxdta setup up above
      //
      lpSelW->bAttr = (BYTE)lpxdta->dwAttrs;
      lpSelW->ftTime = lpxdta->ftLastWriteTime;
      lpSelW->dwSize = lpxdta->qFileSize.LowPart;

      pszFileName = lpSelW->szName;

   } else {

      lpSelA->bAttr = (BYTE)lpxdta->dwAttrs;
      lpSelA->ftTime = lpxdta->ftLastWriteTime;
      lpSelA->dwSize = lpxdta->qFileSize.LowPart;

      pszFileName = szPath;
   }

   if (bSearch) {

      lstrcpy(pszFileName, MemGetFileName(lpxdta));

      //
      // The search window can have any random directory for
      // each item, so don't use szExtSelDirShort caching
      //
      if (!bLFNAware) {

	 GetShortPathName(MemGetFileName(lpxdta), pszFileName, COUNTOF(lpSelW->szName));
      }

   } else {

      //
      // If we are LFNAware, then we need to get the dir.
      //
      if (bLFNAware) {

         lstrcpy(pszFileName, szExtSelDir);
         lstrcat(pszFileName, MemGetFileName(lpxdta));

      } else {

         //
         // Need short dir; use cache.
         //
         lstrcpy(pszFileName, szExtSelDirShort);
         lstrcat(pszFileName,
                 pszAlternateFileName[0] ?
                    pszAlternateFileName :
                    MemGetFileName(lpxdta));
      }

   }

   if (!bUnicode) {

      //
      // Not unicode, must do the thunking now
      // from our temp buffer to lpSelA
      //
      bUsedDefaultChar = FALSE;

      if (!WideCharToMultiByte(CP_ACP, 0, szPath, -1, lpSelA->szName,
         COUNTOF(lpSelA->szName), NULL, &bUsedDefaultChar)) {

            lpSelA->szName[0] = CHAR_NULL;
      }

      if (bUsedDefaultChar) {

         if (!WideCharToMultiByte(CP_ACP, 0, szPath, -1, lpSelA->szName,
            COUNTOF(lpSelA->szName), NULL, &bUsedDefaultChar)) {

            lpSelA->szName[0] = CHAR_NULL;
         }
      }
   }

   return (LONG)uSel;
}