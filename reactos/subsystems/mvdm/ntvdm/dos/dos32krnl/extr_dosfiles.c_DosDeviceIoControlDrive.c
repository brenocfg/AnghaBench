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
typedef  int WORD ;
struct TYPE_2__ {char CurrentDrive; void* LastErrorCode; } ;
typedef  int* PWORD ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  char CHAR ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,char*,...) ; 
#define  DRIVE_CDROM 134 
#define  DRIVE_FIXED 133 
#define  DRIVE_NO_ROOT_DIR 132 
#define  DRIVE_RAMDISK 131 
#define  DRIVE_REMOTE 130 
#define  DRIVE_REMOVABLE 129 
#define  DRIVE_UNKNOWN 128 
 void* ERROR_INVALID_FUNCTION ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDriveTypeA (char*) ; 
 TYPE_1__* Sda ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

BOOLEAN DosDeviceIoControlDrive(WORD DriveNumber, BYTE ControlCode, DWORD Buffer, PWORD Result)
{
    CHAR RootPath[] = "?:\\";

    if (DriveNumber == 0x00)
        RootPath[0] = 'A' + Sda->CurrentDrive;
    else
        RootPath[0] = 'A' + DriveNumber - 1;

    switch (ControlCode)
    {
        case 0x04:
            DPRINT1("UNIMPLEMENTED INT 21h, 4404h, Read from block device %s\n", RootPath);
            Sda->LastErrorCode = ERROR_INVALID_FUNCTION;
            break;
        case 0x05:
            DPRINT1("UNIMPLEMENTED INT 21h, 4405h, Write block device control string %s\n", RootPath);
            Sda->LastErrorCode = ERROR_INVALID_FUNCTION;
            break;
        case 0x08:
        {
            DWORD DriveType = GetDriveTypeA(RootPath);

            switch (DriveType)
            {
            case DRIVE_UNKNOWN:
            case DRIVE_NO_ROOT_DIR:
            default:
                DPRINT1("INT 21h, 4408h, %s -> DriveType = 0x%x\n", RootPath, DriveType);
                *Result = 0x000f;
                return TRUE;
            case DRIVE_REMOVABLE:
            case DRIVE_CDROM:
                *Result = 0x0000;
                return TRUE;
            case DRIVE_FIXED:
                *Result = 0x0001;
                return TRUE;
            case DRIVE_REMOTE:
            case DRIVE_RAMDISK: // ??
                break;
            }
            Sda->LastErrorCode = ERROR_INVALID_FUNCTION;
            return FALSE;
        }
        case 0x09:
            DPRINT1("UNIMPLEMENTED INT 21h, 4409h, Determine if a logical device is local or remote %s\n", RootPath);
            Sda->LastErrorCode = ERROR_INVALID_FUNCTION;
            return FALSE;
        default:
            assert(0);
            break;
    }

    return FALSE;
}