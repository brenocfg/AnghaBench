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
struct TYPE_6__ {int ModeInformationLength; int NumModes; int NumberOfPlanes; int AttributeFlags; int BitsPerPlane; int VisScreenWidth; scalar_t__ Length; } ;
typedef  TYPE_1__ VIDEO_NUM_MODES ;
typedef  int ULONG ;
typedef  TYPE_1__* PVIDEO_MODE_INFORMATION ;
typedef  scalar_t__ PUCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_TAG ; 
 int /*<<< orphan*/  DISPDBG (int /*<<< orphan*/ ) ; 
 scalar_t__ EngAllocMem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ EngDeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  EngFreeMem (TYPE_1__*) ; 
 int /*<<< orphan*/  IOCTL_VIDEO_QUERY_AVAIL_MODES ; 
 int /*<<< orphan*/  IOCTL_VIDEO_QUERY_NUM_AVAIL_MODES ; 
 int VIDEO_MODE_GRAPHICS ; 

DWORD getAvailableModes(
HANDLE hDriver,
PVIDEO_MODE_INFORMATION *modeInformation,
DWORD *cbModeSize)
{
    ULONG ulTemp;
    VIDEO_NUM_MODES modes;
    PVIDEO_MODE_INFORMATION pVideoTemp;

    //
    // Get the number of modes supported by the mini-port
    //

    if (EngDeviceIoControl(hDriver,
                           IOCTL_VIDEO_QUERY_NUM_AVAIL_MODES,
                           NULL,
                           0,
                           &modes,
                           sizeof(VIDEO_NUM_MODES),
                           &ulTemp))
    {
        DISPDBG((0, "getAvailableModes failed VIDEO_QUERY_NUM_AVAIL_MODES\n"));
        return(0);
    }

    *cbModeSize = modes.ModeInformationLength;

    //
    // Allocate the buffer for the mini-port to write the modes in.
    //

    *modeInformation = (PVIDEO_MODE_INFORMATION)
                        EngAllocMem(0, modes.NumModes *
                                    modes.ModeInformationLength, ALLOC_TAG);

    if (*modeInformation == (PVIDEO_MODE_INFORMATION) NULL)
    {
        DISPDBG((0, "getAvailableModes failed EngAllocMem\n"));

        return 0;
    }

    //
    // Ask the mini-port to fill in the available modes.
    //

    if (EngDeviceIoControl(hDriver,
                           IOCTL_VIDEO_QUERY_AVAIL_MODES,
                           NULL,
                           0,
                           *modeInformation,
                           modes.NumModes * modes.ModeInformationLength,
                           &ulTemp))
    {

        DISPDBG((0, "getAvailableModes failed VIDEO_QUERY_AVAIL_MODES\n"));

        EngFreeMem(*modeInformation);
        *modeInformation = (PVIDEO_MODE_INFORMATION) NULL;

        return(0);
    }

    //
    // Now see which of these modes are supported by the display driver.
    // As an internal mechanism, set the length to 0 for the modes we
    // DO NOT support.
    //

    ulTemp = modes.NumModes;
    pVideoTemp = *modeInformation;

// eVb: 2.5 [VGARISC CHANGE] - Add correct mode checks for VGA
    //
    // Mode is rejected if it is not 4 planes, or not graphics, or is not
    // one of 1 bits per pel.
    //

    while (ulTemp--)
    {
        if ((pVideoTemp->NumberOfPlanes != 4 ) ||
            !(pVideoTemp->AttributeFlags & VIDEO_MODE_GRAPHICS) ||
            ((pVideoTemp->BitsPerPlane != 1) ||
             (pVideoTemp->VisScreenWidth > 800)))
// eVb: 2.5 [END]
        {
            pVideoTemp->Length = 0;
        }

        pVideoTemp = (PVIDEO_MODE_INFORMATION)
            (((PUCHAR)pVideoTemp) + modes.ModeInformationLength);
    }

    return modes.NumModes;

}