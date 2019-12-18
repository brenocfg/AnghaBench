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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_5__ {int /*<<< orphan*/  LastErrorCode; } ;
struct TYPE_4__ {int DeviceInfo; int /*<<< orphan*/  Win32Handle; } ;
typedef  TYPE_1__* PDOS_FILE_DESCRIPTOR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 TYPE_1__* DosGetHandleFileDescriptor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_INFO_DEVICE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LockFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* Sda ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN DosLockFile(WORD DosHandle, DWORD Offset, DWORD Size)
{
    PDOS_FILE_DESCRIPTOR Descriptor = DosGetHandleFileDescriptor(DosHandle);

    if (Descriptor == NULL)
    {
        /* Invalid handle */
        Sda->LastErrorCode = ERROR_INVALID_HANDLE;
        return FALSE;
    }

    /* Always succeed for character devices */
    if (Descriptor->DeviceInfo & FILE_INFO_DEVICE) return TRUE;

    if (!LockFile(Descriptor->Win32Handle, Offset, 0, Size, 0))
    {
        Sda->LastErrorCode = GetLastError();
        return FALSE;
    }

    return TRUE;
}