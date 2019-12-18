#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
struct TYPE_3__ {size_t Count; scalar_t__* Drives; } ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  Drives ;
typedef  size_t DWORD ;
typedef  TYPE_1__ DRIVES_LIST ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IOCTL_VCDROM_ENUMERATE_DRIVES ; 
 scalar_t__ OpenMaster () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

BOOLEAN
IsLetterOwned(WCHAR Letter)
{
    HANDLE hDev;
    BOOLEAN Res;
    DRIVES_LIST Drives;
    DWORD i, BytesRead;

    /* We've to deal with driver */
    hDev = OpenMaster();
    if (hDev == INVALID_HANDLE_VALUE)
    {
        _ftprintf(stderr, _T("Failed to open VCD: %x\n"), GetLastError());
        return FALSE;
    }

    /* Get the list of the managed drives */
    Res = DeviceIoControl(hDev, IOCTL_VCDROM_ENUMERATE_DRIVES, NULL, 0, &Drives, sizeof(Drives), &BytesRead, NULL);
    if (!Res)
    {
        _ftprintf(stderr, _T("Failed to enumerate drives: %x\n"), GetLastError());
        CloseHandle(hDev);
        return FALSE;
    }

    /* Don't leak ;-) */
    CloseHandle(hDev);

    /* Do we find our letter in the list? */
    for (i = 0; i < Drives.Count; ++i)
    {
        if (Drives.Drives[i] == Letter)
        {
            break;
        }
    }

    /* No? Fail */
    if (i == Drives.Count)
    {
        _ftprintf(stderr, _T("%c is not a drive owned by VCD\n"), Letter);
        return FALSE;
    }

    /* Otherwise, that's fine! */
    return TRUE;
}