#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ModeInformationLength; int NumModes; int NumberOfPlanes; int AttributeFlags; int BitsPerPlane; scalar_t__ Length; } ;
typedef  TYPE_1__ VIDEO_NUM_MODES ;
typedef  int ULONG ;
typedef  TYPE_1__* PVIDEO_MODE_INFORMATION ;
typedef  scalar_t__ PUCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 scalar_t__ EngAllocMem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ EngDeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  EngFreeMem (TYPE_1__*) ; 
 int /*<<< orphan*/  IOCTL_VIDEO_QUERY_AVAIL_MODES ; 
 int /*<<< orphan*/  IOCTL_VIDEO_QUERY_NUM_AVAIL_MODES ; 
 int VIDEO_MODE_GRAPHICS ; 

DWORD
GetAvailableModes(
   HANDLE hDriver,
   PVIDEO_MODE_INFORMATION *ModeInfo,
   DWORD *ModeInfoSize)
{
   ULONG ulTemp;
   VIDEO_NUM_MODES Modes;
   PVIDEO_MODE_INFORMATION ModeInfoPtr;

   /*
    * Get the number of modes supported by the mini-port
    */

   if (EngDeviceIoControl(hDriver, IOCTL_VIDEO_QUERY_NUM_AVAIL_MODES, NULL,
                          0, &Modes, sizeof(VIDEO_NUM_MODES), &ulTemp))
   {
      return 0;
   }

   *ModeInfoSize = Modes.ModeInformationLength;

   /*
    * Allocate the buffer for the miniport to write the modes in.
    */

   *ModeInfo = (PVIDEO_MODE_INFORMATION)EngAllocMem(0, Modes.NumModes *
      Modes.ModeInformationLength, ALLOC_TAG);

   if (*ModeInfo == NULL)
   {
      return 0;
   }

   /*
    * Ask the miniport to fill in the available modes.
    */

   if (EngDeviceIoControl(hDriver, IOCTL_VIDEO_QUERY_AVAIL_MODES, NULL, 0,
                          *ModeInfo, Modes.NumModes * Modes.ModeInformationLength,
                          &ulTemp))
   {
      EngFreeMem(*ModeInfo);
      *ModeInfo = (PVIDEO_MODE_INFORMATION)NULL;
      return 0;
   }

   /*
    * Now see which of these modes are supported by the display driver.
    * As an internal mechanism, set the length to 0 for the modes we
    * DO NOT support.
    */

   ulTemp = Modes.NumModes;
   ModeInfoPtr = *ModeInfo;

   /*
    * Mode is rejected if it is not one plane, or not graphics, or is not
    * one of 8, 16 or 32 bits per pel.
    */

   while (ulTemp--)
   {
       /* FIXME add banked graphic mode */
      if ((ModeInfoPtr->NumberOfPlanes != 1) ||
          !(ModeInfoPtr->AttributeFlags & VIDEO_MODE_GRAPHICS) ||
          ((ModeInfoPtr->BitsPerPlane != 8) &&
           (ModeInfoPtr->BitsPerPlane != 16) &&
           (ModeInfoPtr->BitsPerPlane != 24) &&
           (ModeInfoPtr->BitsPerPlane != 32)))
      {
         ModeInfoPtr->Length = 0;
      }

      ModeInfoPtr = (PVIDEO_MODE_INFORMATION)
         (((PUCHAR)ModeInfoPtr) + Modes.ModeInformationLength);
   }

   return Modes.NumModes;
}