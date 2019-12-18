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
struct TYPE_2__ {scalar_t__ bRemembered; } ;
typedef  int INT ;
typedef  size_t DRIVE ;

/* Variables and functions */
 scalar_t__ IsCDRomDrive (size_t) ; 
 scalar_t__ IsRamDrive (size_t) ; 
 scalar_t__ IsRemoteDrive (size_t) ; 
 scalar_t__ IsRemovableDrive (size_t) ; 
 TYPE_1__* aDriveInfo ; 
 int dxDriveBitmap ; 

INT
GetDriveOffset(register DRIVE drive)
{
   if (IsRemoteDrive(drive)) {

      if (aDriveInfo[drive].bRemembered)
         return dxDriveBitmap * 5;
      else
         return dxDriveBitmap * 4;
   }


   if (IsRemovableDrive(drive))
      return dxDriveBitmap * 1;

   if (IsRamDrive(drive))
      return dxDriveBitmap * 3;

   if (IsCDRomDrive(drive))
      return dxDriveBitmap * 0;

   return dxDriveBitmap * 2;
}