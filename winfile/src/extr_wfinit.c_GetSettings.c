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
typedef  int WORD ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  void* INT ;

/* Variables and functions */
 void* ANSI_CHARSET ; 
 int /*<<< orphan*/  CLIP_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  COUNTOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateFont (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int DEFAULT_PITCH ; 
 int /*<<< orphan*/  DEFAULT_QUALITY ; 
 int DefaultLayoutRTL () ; 
 int FF_SWISS ; 
 void* GetHeightFromPointsString (int /*<<< orphan*/ *) ; 
 void* GetPrivateProfileInt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetPrivateProfileString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUT_DEFAULT_PRECIS ; 
 int SHIFTJIS_CHARSET ; 
 int TA_ITALIC ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int bConfirmDelete ; 
 int bConfirmFormat ; 
 int bConfirmMouse ; 
 int bConfirmReadOnly ; 
 int bConfirmReplace ; 
 int bConfirmSubDel ; 
 int bDisableVisualStyles ; 
 int bDriveBar ; 
 int bIndexOnLaunch ; 
 scalar_t__ bJAPAN ; 
 int bMinOnRun ; 
 void* bMirrorContent ; 
 int bNewWinOnConnect ; 
 int bSaveSettings ; 
 int bStatusBar ; 
 int bToolbar ; 
 int /*<<< orphan*/  hFont ; 
 int /*<<< orphan*/  szChangeNotifyTime ; 
 int /*<<< orphan*/  szConfirmDelete ; 
 int /*<<< orphan*/  szConfirmFormat ; 
 int /*<<< orphan*/  szConfirmMouse ; 
 int /*<<< orphan*/  szConfirmReadOnly ; 
 int /*<<< orphan*/  szConfirmReplace ; 
 int /*<<< orphan*/  szConfirmSubDel ; 
 int /*<<< orphan*/  szDisableVisualStyles ; 
 int /*<<< orphan*/  szDriveBar ; 
 int /*<<< orphan*/  szFace ; 
 int /*<<< orphan*/  szFaceWeight ; 
 int /*<<< orphan*/  szHelv ; 
 int /*<<< orphan*/  szIndexOnLaunch ; 
 int /*<<< orphan*/  szLowerCase ; 
 int /*<<< orphan*/  szMinOnRun ; 
 int /*<<< orphan*/  szMirrorContent ; 
 int /*<<< orphan*/  szNewWinOnNetConnect ; 
 int /*<<< orphan*/  szSaveCharset ; 
 int /*<<< orphan*/  szSaveSettings ; 
 int /*<<< orphan*/  szSettings ; 
 int /*<<< orphan*/  szSize ; 
 int /*<<< orphan*/  szStatusBar ; 
 int /*<<< orphan*/  szTheINIFile ; 
 int /*<<< orphan*/  szToolbar ; 
 int uChangeNotifyTime ; 
 int wTextAttribs ; 

VOID
GetSettings()
{
   TCHAR szTemp[128];
   INT size;
   INT weight;

   INT bfCharset;

   /* Get the flags out of the INI file. */
   bMinOnRun            = GetPrivateProfileInt(szSettings, szMinOnRun,            bMinOnRun,            szTheINIFile);
   bIndexOnLaunch       = GetPrivateProfileInt(szSettings, szIndexOnLaunch,       bIndexOnLaunch,       szTheINIFile);
   wTextAttribs         = (WORD)GetPrivateProfileInt(szSettings, szLowerCase,     wTextAttribs,         szTheINIFile);
   bStatusBar           = GetPrivateProfileInt(szSettings, szStatusBar,           bStatusBar,           szTheINIFile);
   bDisableVisualStyles = GetPrivateProfileInt(szSettings, szDisableVisualStyles, bDisableVisualStyles, szTheINIFile);
   bMirrorContent       = GetPrivateProfileInt(szSettings, szMirrorContent,    DefaultLayoutRTL(), szTheINIFile);

   bDriveBar       = GetPrivateProfileInt(szSettings, szDriveBar,      bDriveBar,      szTheINIFile);
   bToolbar        = GetPrivateProfileInt(szSettings, szToolbar,       bToolbar,       szTheINIFile);

   bNewWinOnConnect = GetPrivateProfileInt(szSettings, szNewWinOnNetConnect, bNewWinOnConnect, szTheINIFile);
   bConfirmDelete  = GetPrivateProfileInt(szSettings, szConfirmDelete, bConfirmDelete, szTheINIFile);
   bConfirmSubDel  = GetPrivateProfileInt(szSettings, szConfirmSubDel, bConfirmSubDel, szTheINIFile);
   bConfirmReplace = GetPrivateProfileInt(szSettings, szConfirmReplace,bConfirmReplace,szTheINIFile);
   bConfirmMouse   = GetPrivateProfileInt(szSettings, szConfirmMouse,  bConfirmMouse,  szTheINIFile);
   bConfirmFormat  = GetPrivateProfileInt(szSettings, szConfirmFormat, bConfirmFormat, szTheINIFile);
   bConfirmReadOnly= GetPrivateProfileInt(szSettings, szConfirmReadOnly, bConfirmReadOnly, szTheINIFile);
   uChangeNotifyTime= GetPrivateProfileInt(szSettings, szChangeNotifyTime, uChangeNotifyTime, szTheINIFile);
   bSaveSettings   = GetPrivateProfileInt(szSettings, szSaveSettings,  bSaveSettings, szTheINIFile);
   weight = GetPrivateProfileInt(szSettings, szFaceWeight, 400, szTheINIFile);

   GetPrivateProfileString(szSettings,
                           szSize,
                           bJAPAN ?
                              TEXT("14") :
                              TEXT("8"),
                           szTemp,
                           COUNTOF(szTemp),
                           szTheINIFile);

   size = GetHeightFromPointsString(szTemp);

   GetPrivateProfileString(szSettings,
                           szFace,
			   szHelv,
                           szTemp,
                           COUNTOF(szTemp),
                           szTheINIFile);


   bfCharset = bJAPAN ?
                  GetPrivateProfileInt(szSettings,
                                       szSaveCharset,
                                       SHIFTJIS_CHARSET,
                                       szTheINIFile) :
                  ANSI_CHARSET;

   hFont = CreateFont(size,
                      0, 0, 0, weight,
                      wTextAttribs & TA_ITALIC, 0, 0,
                      bfCharset,
                      OUT_DEFAULT_PRECIS,
                      CLIP_DEFAULT_PRECIS,
                      DEFAULT_QUALITY,
                      DEFAULT_PITCH | FF_SWISS,
                      szTemp);

}