#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINT_PTR ;
typedef  void* UINT ;
struct TYPE_6__ {void* bRestored; scalar_t__ iStartBmp; scalar_t__ idBitmap; int /*<<< orphan*/ * hbmButtons; void* bUnicode; scalar_t__ hMenu; scalar_t__ hModule; void* Delta; scalar_t__ (* ExtProc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int dwSize; int /*<<< orphan*/  szMenuName; scalar_t__ hMenu; void* wMenuDelta; } ;
struct TYPE_4__ {int dwSize; int /*<<< orphan*/  szMenuName; scalar_t__ hMenu; void* wMenuDelta; } ;
typedef  scalar_t__ TCHAR ;
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HMENU ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ (* FM_EXT_PROC ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  TYPE_1__ FMS_LOADW ;
typedef  TYPE_2__ FMS_LOADA ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BiasMenu (scalar_t__,void*) ; 
 int /*<<< orphan*/  COUNTOF (scalar_t__*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FMEVENT_LOAD ; 
 int /*<<< orphan*/  FM_EXT_PROC_ENTRYA ; 
 int /*<<< orphan*/  FM_EXT_PROC_ENTRYW ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 scalar_t__ GetMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetPrivateProfileString (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (scalar_t__,int /*<<< orphan*/ ) ; 
 int IDM_EXTENSIONS ; 
 int /*<<< orphan*/  InsertMenuA (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InsertMenuW (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LoadLibrary (scalar_t__*) ; 
 int MAXPATHLEN ; 
 int MAX_EXTENSIONS ; 
 int MF_BYPOSITION ; 
 int MF_POPUP ; 
 scalar_t__ MapIDMToMenuPos (int) ; 
 int PROFILE_STRING_SIZ ; 
 void* TRUE ; 
 int /*<<< orphan*/  bSecMenuDeleted ; 
 TYPE_3__* extensions ; 
 int /*<<< orphan*/  hwndFrame ; 
 int iNumExtensions ; 
 scalar_t__ lstrlen (scalar_t__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szAddons ; 
 int /*<<< orphan*/  szNULL ; 
 int /*<<< orphan*/  szTheINIFile ; 

VOID
InitExtensions()
{
   TCHAR szBuf[PROFILE_STRING_SIZ];
   TCHAR szPath[MAXPATHLEN];
   LPTSTR p;
   HANDLE hMod;
   FM_EXT_PROC fp;
   HMENU hMenu;
   INT iMenuBase;
   HMENU hMenuFrame;
   INT iMenuOffset=0;
   BOOL bUnicode;

   hMenuFrame = GetMenu(hwndFrame);

   ASSERT(!bSecMenuDeleted);
   iMenuBase = MapIDMToMenuPos(IDM_EXTENSIONS);

   GetPrivateProfileString(szAddons, NULL, szNULL, szBuf, COUNTOF(szBuf), szTheINIFile);

   for (p = szBuf; *p && iNumExtensions < MAX_EXTENSIONS; p += lstrlen(p) + 1) {

      GetPrivateProfileString(szAddons, p, szNULL, szPath, COUNTOF(szPath), szTheINIFile);

      hMod = LoadLibrary(szPath);

      if (hMod) {
         fp = (FM_EXT_PROC)GetProcAddress(hMod, FM_EXT_PROC_ENTRYW);
         if (fp) {
            bUnicode = TRUE;
         } else {
            fp = (FM_EXT_PROC)GetProcAddress(hMod, FM_EXT_PROC_ENTRYA);
            bUnicode = FALSE;
         }

         if (fp) {
            UINT bias;
            FMS_LOADA lsA;
            FMS_LOADW lsW;

            bias = ((IDM_EXTENSIONS + iNumExtensions + 1)*100);

            // We are now going to bias each menu, since extensions
            // don't know about each other and may clash IDM_xx if
            // we don't.

            // Our system is as follow:  IDMs 100 - 699 are reserved
            // for us (menus 0 - 5 inclusive).  Thus, IDMs
            // 700 - 1699 is reserved for extensions.
            // This is why we added 1 in the above line to compute
            // NOTE: IDMs 0000-0099 are not used for menu 0.

            if (bUnicode)
               lsW.wMenuDelta = bias;
            else
               lsA.wMenuDelta = bias;

            if ((*fp)(hwndFrame, FMEVENT_LOAD, bUnicode ? (LPARAM)&lsW : (LPARAM)&lsA)) {

               if ((bUnicode ? lsW.dwSize : lsA.dwSize)
                  != (bUnicode ? sizeof(FMS_LOADW) : sizeof(FMS_LOADA)))
                  goto LoadFail;

               hMenu = bUnicode ? lsW.hMenu : lsA.hMenu;

               extensions[iNumExtensions].ExtProc = fp;
               extensions[iNumExtensions].Delta = bias;
               extensions[iNumExtensions].hModule = hMod;
               extensions[iNumExtensions].hMenu = hMenu;
               extensions[iNumExtensions].bUnicode = bUnicode;

               // these are set when FMEVENT_TOOLBARLOAD is called
               extensions[iNumExtensions].hbmButtons = NULL;
               extensions[iNumExtensions].idBitmap = 0;
               extensions[iNumExtensions].iStartBmp = 0;
               extensions[iNumExtensions].bRestored = FALSE;

               if (hMenu) {
                  BiasMenu(hMenu, bias);

                  if (bUnicode) {
                     InsertMenuW(hMenuFrame,
                        iMenuBase + iMenuOffset,
                        MF_BYPOSITION | MF_POPUP,
                        (UINT_PTR) hMenu, lsW.szMenuName);
                  } else {
                     InsertMenuA(hMenuFrame,
                        iMenuBase + iMenuOffset,
                        MF_BYPOSITION | MF_POPUP,
                        (UINT_PTR) hMenu, lsA.szMenuName);
                  }
                  iMenuOffset++;
               }

               iNumExtensions++;

            } else {
               goto LoadFail;
            }
         } else {
LoadFail:
            FreeLibrary(hMod);
         }
      }
   }
}