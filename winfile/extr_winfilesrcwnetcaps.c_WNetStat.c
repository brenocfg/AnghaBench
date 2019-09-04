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
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__ NS_CONNECT ; 
 scalar_t__ NS_CONNECTDLG ; 
 scalar_t__ NS_PROPERTYDLG ; 
 scalar_t__ NS_SHAREDLG ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 scalar_t__ TRUE ; 

BOOL
WNetStat(INT nIndex)
{
   static DWORD fdwRet = (DWORD)-1;
   DWORD dwError;

   BOOL bNetwork = FALSE;
   BOOL bConnect = FALSE;

   HKEY hKey;

   DWORD dwcbBuffer = 0;

   if (
//
// Disable NS_REFRESH since we test for network installed on disk,
// not network services started.
//
#if NSREFRESH
      NS_REFRESH == nIndex ||
#endif
      (DWORD) -1 == fdwRet) {

      fdwRet = 0;

      //
      // Check for connection dialog
      //

      dwError = RegOpenKey(HKEY_LOCAL_MACHINE,
         TEXT("System\\CurrentControlSet\\Control\\NetworkProvider\\Order"),
         &hKey);

      if (!dwError) {

         dwError = RegQueryValueEx(hKey,
            TEXT("ProviderOrder"),
            NULL,
            NULL,
            NULL,
            &dwcbBuffer);

         if (ERROR_SUCCESS == dwError && dwcbBuffer > 1) {

            bNetwork = TRUE;
         }

         RegCloseKey(hKey);
      }

      if (bNetwork) {
#if 0
         //
         // Check the registry to see if the user can make connections
         //
         dwError = RegOpenKey(HKEY_CURRENT_USER,
            TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\File Manager\\Settings"),
            &hKey);

         if (dwError != ERROR_SUCCESS) {
            bConnect = TRUE;
         } else {

            cb = sizeof(dwTemp);
            dwTemp = 0;

            dwError = RegQueryValueEx(hKey, TEXT("Network"),
               NULL, NULL, (LPBYTE)&dwTemp, &cb);

            if (dwError != ERROR_SUCCESS || dwTemp)
               bConnect = TRUE;

            RegCloseKey(hKey);
         }


         if (bConnect) {
            fdwRet |= NS_CONNECTDLG|NS_CONNECT;
         }
#else
         fdwRet |= NS_CONNECTDLG|NS_CONNECT;
#endif
      }

      //
      // Check for share-ability
      //

      dwError = RegOpenKey(HKEY_LOCAL_MACHINE,
         TEXT("System\\CurrentControlSet\\Services\\LanmanServer"),
         &hKey);

      if (!dwError) {

         fdwRet |= NS_SHAREDLG|NS_PROPERTYDLG;
         RegCloseKey(hKey);
      }
   }

   return fdwRet & nIndex ? TRUE : FALSE;
}