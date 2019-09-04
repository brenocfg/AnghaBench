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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {scalar_t__ RequestedVirtualAddress; } ;
typedef  TYPE_1__ VIDEO_MEMORY ;
struct TYPE_6__ {int /*<<< orphan*/  hDriver; scalar_t__ pjScreen; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_2__* PPDEV ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ EngDeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOCTL_VIDEO_UNMAP_VIDEO_MEMORY ; 
 int /*<<< orphan*/  RIP (char*) ; 

VOID vDisableSURF(PPDEV ppdev)
{
    DWORD returnedDataLength;
    VIDEO_MEMORY videoMemory;

    videoMemory.RequestedVirtualAddress = (PVOID) ppdev->pjScreen;

    if (EngDeviceIoControl(ppdev->hDriver,
                           IOCTL_VIDEO_UNMAP_VIDEO_MEMORY,
                           &videoMemory,
                           sizeof(VIDEO_MEMORY),
                           NULL,
                           0,
                           &returnedDataLength))
    {
        RIP("DISP vDisableSURF failed IOCTL_VIDEO_UNMAP\n");
    }
}