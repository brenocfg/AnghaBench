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
struct TYPE_6__ {void* bShareChkTried; void* bShareChkFail; } ;
struct TYPE_5__ {int /*<<< orphan*/  dwNetType; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__* PDNODE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  size_t DRIVE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t DRIVEID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetTreePath (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int MAXPATHLEN ; 
 void* TRUE ; 
 int /*<<< orphan*/  WAITNET_TYPELOADED ; 
 scalar_t__ WN_SUCCESS ; 
 scalar_t__ WNetGetDirectoryType (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* aDriveInfo ; 

BOOL
IsNetPath(PDNODE pNode)
{
   // 2* buffer for single file overflow
   TCHAR szPath[MAXPATHLEN * 2];
   DWORD dwType;
   DRIVE drive;


   if (!WAITNET_TYPELOADED)
      return FALSE;

   //
   // Only do WNetGetDirectoryType if the drive
   // hasn't failed before on this call.
   //
   if (pNode->dwNetType == (DWORD)-1)
   {
      GetTreePath(pNode, szPath);
      drive = DRIVEID(szPath);

      if (!aDriveInfo[drive].bShareChkFail &&
          WNetGetDirectoryType( szPath,
                                &dwType,
                                !aDriveInfo[drive].bShareChkTried ) == WN_SUCCESS)
      {
         pNode->dwNetType = dwType;
      }
      else
      {
         pNode->dwNetType = 0;
         aDriveInfo[drive].bShareChkFail = TRUE;
      }

      aDriveInfo[drive].bShareChkTried = TRUE;
   }

   return pNode->dwNetType;
}