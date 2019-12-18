#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lpRemoteName; int /*<<< orphan*/  lpProvider; } ;
typedef  TYPE_1__ WNET_CONNECTIONINFO ;
struct TYPE_5__ {size_t* lpszRemoteNameMinusFour; size_t* dwRemoteNameMax; int* dwLines; size_t dwAltNameError; TYPE_1__* lpConnectInfo; } ;
typedef  TYPE_2__* PDRIVEINFO ;
typedef  size_t LPTSTR ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HLOCAL ;
typedef  size_t DWORD ;
typedef  size_t DRIVE ;

/* Variables and functions */
 int /*<<< orphan*/  ByteCountOf (size_t) ; 
 size_t DRIVE_INFO_NAME_HEADER ; 
 size_t ERROR_MORE_DATA ; 
 size_t ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 size_t MAX_ALTNAME ; 
 int /*<<< orphan*/  NetCon_UpdateLines (size_t,size_t) ; 
 size_t REMOTE_DEFAULT_SIZE ; 
 size_t WNetFormatNetworkNameW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* aDriveInfo ; 
 int /*<<< orphan*/ * adwAltNameTrans ; 
 int /*<<< orphan*/  cchDriveListMax ; 

INT
NetCon_UpdateAltName(DRIVE drive, DWORD dwRetVal)
{
   PDRIVEINFO pDriveInfo = &aDriveInfo[drive];
   LPTSTR lpszBuf;
   DWORD dwSize;
   WNET_CONNECTIONINFO * lpConnectInfo = pDriveInfo->lpConnectInfo;
   DWORD i;

   for (i = 0; i < MAX_ALTNAME; i++) {

      //
      // If dwRetVal is in error state,
      // fail for all.
      //
      if (dwRetVal)
         break;

      lpszBuf = pDriveInfo->lpszRemoteNameMinusFour[i];
      dwSize = pDriveInfo->dwRemoteNameMax[i];

      if (!dwSize)
         dwSize = REMOTE_DEFAULT_SIZE;

      if (!lpszBuf) {
Retry:
         lpszBuf = (LPTSTR) LocalAlloc(LPTR, ByteCountOf(dwSize + DRIVE_INFO_NAME_HEADER));
      }


      pDriveInfo->lpszRemoteNameMinusFour[i] = lpszBuf;

      if (!lpszBuf) {

         pDriveInfo->dwRemoteNameMax[i]=0;

         dwRetVal = ERROR_NOT_ENOUGH_MEMORY;
         goto Done;
      }

      dwRetVal = WNetFormatNetworkNameW(lpConnectInfo->lpProvider,
         lpConnectInfo->lpRemoteName,
         lpszBuf + DRIVE_INFO_NAME_HEADER,
         &dwSize,
         adwAltNameTrans[i],
         cchDriveListMax);

      if (ERROR_MORE_DATA == dwRetVal) {

         //
         // If need more space, free buffer and retry
         // (dwSize is updated by WNetFormatNetworkName)
         //

         LocalFree((HLOCAL)lpszBuf);
         goto Retry;
      }

      if (dwRetVal) {
         break;
      }

      NetCon_UpdateLines(drive, i);
   }
Done:
   if (dwRetVal)
   {
      //
      // Set everything to 1!
      //
      for (i = 0; i < MAX_ALTNAME; i++)
      {
         pDriveInfo->dwLines[i] = 1;
      }
   }
   pDriveInfo->dwAltNameError = dwRetVal;
   return dwRetVal;
}