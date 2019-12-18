#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  bRefresh; scalar_t__ bValid; } ;
struct TYPE_4__ {TYPE_1__ sVolInfo; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  scalar_t__ DWORD ;
typedef  size_t DRIVEIND ;
typedef  size_t DRIVE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ALTNAME_REG ; 
 int /*<<< orphan*/  CHAR_COLON ; 
 int /*<<< orphan*/  CHAR_NULL ; 
 int /*<<< orphan*/  CHAR_SPACE ; 
 scalar_t__ COUNTOF (int /*<<< orphan*/ *) ; 
 scalar_t__ DE_REGNAME ; 
 int /*<<< orphan*/  DRIVESET (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ GetVolShare (size_t,int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  IsCDRomDrive (size_t) ; 
 int /*<<< orphan*/  IsRemovableDrive (size_t) ; 
 int /*<<< orphan*/  StrNCpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* aDriveInfo ; 
 size_t* rgiDrive ; 

VOID
BuildDriveLine(LPTSTR* ppszTemp, DRIVEIND driveInd,
   BOOL fGetFloppyLabel, DWORD dwType)
{
   static TCHAR szDrive[64];
   DRIVE drive;
   LPTSTR p;
   DWORD dwError;

   drive = rgiDrive[driveInd];

   //
   // If !fGetFloppyLabel, but our VolInfo is valid,
   // we might as well just pick it up.
   //

   if (fGetFloppyLabel || (!IsRemovableDrive(drive) && !IsCDRomDrive(drive)) ||
      (aDriveInfo[drive].sVolInfo.bValid && !aDriveInfo[drive].sVolInfo.bRefresh)) {

      if (dwError = GetVolShare(rgiDrive[driveInd], ppszTemp, dwType)) {

         if (DE_REGNAME == dwError) {

            goto UseRegName;
         }

         goto Failed;

      } else {

         //
         // If regular name, do copy
         //
         if (ALTNAME_REG == dwType) {

UseRegName:

            p = *ppszTemp;

            *ppszTemp = szDrive;
            StrNCpy(szDrive+3, p, COUNTOF(szDrive)-4);

         } else {

            //
            // Assume header is valid!
            //
            (*ppszTemp) -=3;
         }
      }

   } else {

Failed:

      *ppszTemp = szDrive;

      //
      // Delimit
      //
      (*ppszTemp)[3]=CHAR_NULL;
   }

   DRIVESET(*ppszTemp,rgiDrive[driveInd]);

   (*ppszTemp)[1] = CHAR_COLON;
   (*ppszTemp)[2] = CHAR_SPACE;
}