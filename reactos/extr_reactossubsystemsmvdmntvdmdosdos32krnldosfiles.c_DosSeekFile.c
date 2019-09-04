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
typedef  scalar_t__ WORD ;
struct TYPE_3__ {int DeviceInfo; scalar_t__ Position; int /*<<< orphan*/  Win32Handle; } ;
typedef  TYPE_1__* PDOS_FILE_DESCRIPTOR ;
typedef  scalar_t__* LPDWORD ;
typedef  int /*<<< orphan*/  LONG ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* DosGetHandleFileDescriptor (scalar_t__) ; 
 scalar_t__ ERROR_INVALID_FUNCTION ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  FILE_CURRENT ; 
 int /*<<< orphan*/  FILE_END ; 
 int FILE_INFO_DEVICE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_SET_FILE_POINTER ; 
 scalar_t__ SetFilePointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

WORD DosSeekFile(WORD FileHandle,
                 LONG Offset,
                 BYTE Origin,
                 LPDWORD NewOffset)
{
    WORD Result = ERROR_SUCCESS;
    DWORD FilePointer;
    PDOS_FILE_DESCRIPTOR Descriptor = DosGetHandleFileDescriptor(FileHandle);

    DPRINT("DosSeekFile: FileHandle 0x%04X, Offset 0x%08X, Origin 0x%02X\n",
           FileHandle, Offset, Origin);

    if (Descriptor == NULL)
    {
        /* Invalid handle */
        return ERROR_INVALID_HANDLE;
    }

    if (Descriptor->DeviceInfo & FILE_INFO_DEVICE)
    {
        /* For character devices, always return success */
        return ERROR_SUCCESS;
    }

    /* Check if the origin is valid */
    if (Origin != FILE_BEGIN && Origin != FILE_CURRENT && Origin != FILE_END)
    {
        return ERROR_INVALID_FUNCTION;
    }

    FilePointer = SetFilePointer(Descriptor->Win32Handle, Offset, NULL, Origin);

    /* Check if there's a possibility the operation failed */
    if (FilePointer == INVALID_SET_FILE_POINTER)
    {
        /* Get the real error code */
        Result = (WORD)GetLastError();
    }

    if (Result != ERROR_SUCCESS)
    {
        /* The operation did fail */
        return Result;
    }

    /* Update the position */
    Descriptor->Position = FilePointer;

    /* Return the file pointer, if requested */
    if (NewOffset) *NewOffset = FilePointer;

    /* Return success */
    return ERROR_SUCCESS;
}