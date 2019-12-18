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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ TCHAR ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  scalar_t__ FM_UNDELETE_PROC ;

/* Variables and functions */
 int /*<<< orphan*/  AddBackslash (scalar_t__*) ; 
 int /*<<< orphan*/  COUNTOF (scalar_t__*) ; 
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DrawMenuBar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetPrivateProfileString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetSystemDirectory (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDM_CONNECT ; 
 int /*<<< orphan*/  IDM_DISCONNECT ; 
 int /*<<< orphan*/  IDM_DISK ; 
 int /*<<< orphan*/  IDM_DISKCOPY ; 
 int /*<<< orphan*/  IDM_DRIVEBAR ; 
 int /*<<< orphan*/  IDM_FILE ; 
 int /*<<< orphan*/  IDM_INDEXONLAUNCH ; 
 int /*<<< orphan*/  IDM_MINONRUN ; 
 int /*<<< orphan*/  IDM_NEWWINONCONNECT ; 
 int /*<<< orphan*/  IDM_SAVESETTINGS ; 
 int /*<<< orphan*/  IDM_SHAREAS ; 
 int /*<<< orphan*/  IDM_STATUSBAR ; 
 int /*<<< orphan*/  IDM_STOPSHARE ; 
 int /*<<< orphan*/  IDM_TOOLBAR ; 
 int /*<<< orphan*/  IDM_UNDELETE ; 
 int /*<<< orphan*/  IDS_CONNECT ; 
 int /*<<< orphan*/  IDS_DISCONNECT ; 
 int /*<<< orphan*/  IDS_NEWWINONCONNECT ; 
 int /*<<< orphan*/  IDS_SHAREAS ; 
 int /*<<< orphan*/  IDS_STOPSHARE ; 
 int /*<<< orphan*/  IDS_UNDELETE ; 
 int /*<<< orphan*/  InitExtensions () ; 
 int /*<<< orphan*/  InitToolbarButtons () ; 
 int /*<<< orphan*/  InsertMenu (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/ * LoadLibrary (scalar_t__*) ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
 int MF_BYCOMMAND ; 
 int MF_BYPOSITION ; 
 int MF_CHECKED ; 
 int MF_GRAYED ; 
 int MF_SEPARATOR ; 
 int MF_STRING ; 
 int MapIDMToMenuPos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_CONNECTDLG ; 
 int /*<<< orphan*/  NS_SHAREDLG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNDELETE_ENTRYA ; 
 int /*<<< orphan*/  UNDELETE_ENTRYW ; 
 scalar_t__ WNetStat (int /*<<< orphan*/ ) ; 
 scalar_t__ bDriveBar ; 
 scalar_t__ bIndexOnLaunch ; 
 scalar_t__ bMinOnRun ; 
 scalar_t__ bNewWinOnConnect ; 
 scalar_t__ bSaveSettings ; 
 scalar_t__ bStatusBar ; 
 scalar_t__ bToolbar ; 
 int /*<<< orphan*/  bUndeleteUnicode ; 
 int /*<<< orphan*/  hAppInstance ; 
 int /*<<< orphan*/ * hModUndelete ; 
 int /*<<< orphan*/  hwndFrame ; 
 scalar_t__ lpfpUndelete ; 
 int /*<<< orphan*/  lstrcat (scalar_t__*,scalar_t__*) ; 
 scalar_t__ nFloppies ; 
 int /*<<< orphan*/  szNULL ; 
 int /*<<< orphan*/  szSettings ; 
 int /*<<< orphan*/  szTheINIFile ; 
 int /*<<< orphan*/  szUndelete ; 

VOID
InitMenus()
{
   HMENU hMenu;
   TCHAR szValue[MAXPATHLEN];
   HMENU hMenuOptions;

   TCHAR szPathName[MAXPATHLEN];

   GetPrivateProfileString(szSettings, szUndelete, szNULL, szValue, COUNTOF(szValue), szTheINIFile);

   if (szValue[0]) {

      // create explicit filename to avoid searching the path

      GetSystemDirectory(szPathName, COUNTOF(szPathName));
      AddBackslash(szPathName);
      lstrcat(szPathName, szValue);

      hModUndelete = LoadLibrary(szValue);

      if (hModUndelete) {
         lpfpUndelete = (FM_UNDELETE_PROC)GetProcAddress(hModUndelete, UNDELETE_ENTRYW);

         if (lpfpUndelete) {
            bUndeleteUnicode = TRUE;
         } else {
            lpfpUndelete = (FM_UNDELETE_PROC)GetProcAddress(hModUndelete, UNDELETE_ENTRYA);
            bUndeleteUnicode = FALSE;
         }

         if (lpfpUndelete) {
            hMenu = GetSubMenu(GetMenu(hwndFrame), MapIDMToMenuPos(IDM_FILE));
            LoadString(hAppInstance, IDS_UNDELETE, szValue, COUNTOF(szValue));
            InsertMenu(hMenu, 4, MF_BYPOSITION | MF_STRING, IDM_UNDELETE, szValue);
         }
      } else {
         FreeLibrary(hModUndelete);
         hModUndelete = NULL;
      }
   }

   //
   // use submenu because we are doing this by position
   //
   hMenu = GetSubMenu(GetMenu(hwndFrame), MapIDMToMenuPos(IDM_DISK));

   if (WNetStat(NS_CONNECTDLG)) {  // Network Connections...

      InsertMenu(hMenu, 4, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);

      LoadString(hAppInstance, IDS_NEWWINONCONNECT, szValue, COUNTOF(szValue));
      hMenuOptions = GetSubMenu(GetMenu(hwndFrame), 4);
      InsertMenu(hMenuOptions, 8, MF_BYPOSITION | MF_STRING, IDM_NEWWINONCONNECT, szValue);

      LoadString(hAppInstance, IDS_CONNECT, szValue, COUNTOF(szValue));
      InsertMenu(hMenu, 5, MF_BYPOSITION | MF_STRING, IDM_CONNECT, szValue);

      LoadString(hAppInstance, IDS_DISCONNECT, szValue, COUNTOF(szValue));
      InsertMenu(hMenu, 6, MF_BYPOSITION | MF_STRING, IDM_DISCONNECT, szValue);

   }

   // Shared Directories
   if (WNetStat(NS_SHAREDLG)) {

      InsertMenu(hMenu, 7, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);

      LoadString(hAppInstance, IDS_SHAREAS, szValue, COUNTOF(szValue));
      InsertMenu(hMenu, 8, MF_BYPOSITION | MF_STRING, IDM_SHAREAS, szValue);

      LoadString(hAppInstance, IDS_STOPSHARE, szValue, COUNTOF(szValue));
      InsertMenu(hMenu, 9, MF_BYPOSITION | MF_STRING, IDM_STOPSHARE, szValue);

   }

   //
   // Init the Disk menu.
   //
   hMenu = GetMenu(hwndFrame);

   if (nFloppies == 0) {
      EnableMenuItem(hMenu, IDM_DISKCOPY, MF_BYCOMMAND | MF_GRAYED);
   }


   if (bStatusBar)
      CheckMenuItem(hMenu, IDM_STATUSBAR, MF_BYCOMMAND | MF_CHECKED);
   if (bMinOnRun)
      CheckMenuItem(hMenu, IDM_MINONRUN,  MF_BYCOMMAND | MF_CHECKED);
   if (bIndexOnLaunch)
      CheckMenuItem(hMenu, IDM_INDEXONLAUNCH, MF_BYCOMMAND | MF_CHECKED);

   if (bSaveSettings)
      CheckMenuItem(hMenu, IDM_SAVESETTINGS,  MF_BYCOMMAND | MF_CHECKED);

   if (bDriveBar)
      CheckMenuItem(hMenu, IDM_DRIVEBAR, MF_BYCOMMAND | MF_CHECKED);
   if (bToolbar)
      CheckMenuItem(hMenu, IDM_TOOLBAR, MF_BYCOMMAND | MF_CHECKED);

   if (bNewWinOnConnect)
      CheckMenuItem(hMenu, IDM_NEWWINONCONNECT, MF_BYCOMMAND | MF_CHECKED);


   //
   // Init menus after the window/menu has been created
   //
   InitExtensions();

   InitToolbarButtons();

   //
   // Redraw the menu bar since it's already displayed
   //
   DrawMenuBar(hwndFrame);
}