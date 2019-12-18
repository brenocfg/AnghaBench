#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_16__ {int /*<<< orphan*/  CurrentPsp; } ;
struct TYPE_12__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_15__ {int DeviceAttributes; TYPE_1__ Name; int /*<<< orphan*/  Driver; int /*<<< orphan*/  (* OpenRoutine ) (TYPE_4__*) ;} ;
struct TYPE_14__ {int DeviceInfo; int OpenMode; int /*<<< orphan*/  OwnerPsp; scalar_t__ Win32Handle; int /*<<< orphan*/  Size; int /*<<< orphan*/  Attributes; int /*<<< orphan*/  FileName; int /*<<< orphan*/  DevicePointer; } ;
struct TYPE_13__ {int nLength; int bInheritHandle; int /*<<< orphan*/ * lpSecurityDescriptor; } ;
typedef  int /*<<< orphan*/  SecurityAttributes ;
typedef  TYPE_2__ SECURITY_ATTRIBUTES ;
typedef  TYPE_3__* PDOS_FILE_DESCRIPTOR ;
typedef  TYPE_4__* PDOS_DEVICE_NODE ;
typedef  scalar_t__* LPWORD ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int BOOL ;
typedef  int ACCESS_MASK ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (int /*<<< orphan*/ ,int,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ,int) ; 
 int DosFindFreeDescriptor () ; 
 TYPE_4__* DosGetDevice (int /*<<< orphan*/ ) ; 
 TYPE_3__* DosGetFileDescriptor (int) ; 
 scalar_t__ DosOpenHandle (int) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ ERROR_TOO_MANY_OPEN_FILES ; 
 int FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FILE_INFO_DEVICE ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  GetFileAttributesA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_DOS_HANDLE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LOBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlFillMemory (int /*<<< orphan*/ ,int,char) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_3__*,int) ; 
 TYPE_7__* Sda ; 
 int /*<<< orphan*/  StoreNameInSft (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

WORD DosOpenFile(LPWORD Handle,
                 LPCSTR FilePath,
                 BYTE AccessShareModes)
{
    HANDLE FileHandle = NULL;
    PDOS_DEVICE_NODE Node;
    WORD DosHandle;
    BYTE DescriptorId;
    PDOS_FILE_DESCRIPTOR Descriptor;

    DPRINT("DosOpenFile: FilePath \"%s\", AccessShareModes 0x%04X\n",
           FilePath, AccessShareModes);

    //
    // The article about OpenFile API: http://msdn.microsoft.com/en-us/library/windows/desktop/aa365430(v=vs.85).aspx
    // explains what those AccessShareModes are (see the uStyle flag).
    //

    Node = DosGetDevice(FilePath);
    if (Node != NULL)
    {
        if (Node->OpenRoutine) Node->OpenRoutine(Node);
    }
    else
    {
        ACCESS_MASK AccessMode = 0;
        DWORD ShareMode = 0;
        BOOL InheritableFile = FALSE;
        SECURITY_ATTRIBUTES SecurityAttributes;

        /* Parse the access mode */
        switch (AccessShareModes & 0x03)
        {
            /* Read-only */
            case 0:
                AccessMode = GENERIC_READ;
                break;

            /* Write only */
            case 1:
                AccessMode = GENERIC_WRITE;
                break;

            /* Read and write */
            case 2:
                AccessMode = GENERIC_READ | GENERIC_WRITE;
                break;

            /* Invalid */
            default:
                return ERROR_INVALID_PARAMETER;
        }

        /* Parse the share mode */
        switch ((AccessShareModes >> 4) & 0x07)
        {
            /* Compatibility mode */
            case 0:
                ShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE;
                break;

            /* No sharing "DenyAll" */
            case 1:
                ShareMode = 0;
                break;

            /* No write share "DenyWrite" */
            case 2:
                ShareMode = FILE_SHARE_READ;
                break;

            /* No read share "DenyRead" */
            case 3:
                ShareMode = FILE_SHARE_WRITE;
                break;

            /* Full share "DenyNone" */
            case 4:
                ShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
                break;

            /* Invalid */
            default:
                return ERROR_INVALID_PARAMETER;
        }

        /* Check for inheritance */
        InheritableFile = ((AccessShareModes & 0x80) == 0);

        /* Assign default security attributes to the file, and set the inheritance flag */
        SecurityAttributes.nLength = sizeof(SecurityAttributes);
        SecurityAttributes.lpSecurityDescriptor = NULL;
        SecurityAttributes.bInheritHandle = InheritableFile;

        /* Open the file */
        FileHandle = CreateFileA(FilePath,
                                 AccessMode,
                                 ShareMode,
                                 &SecurityAttributes,
                                 OPEN_EXISTING,
                                 FILE_ATTRIBUTE_NORMAL,
                                 NULL);
        if (FileHandle == INVALID_HANDLE_VALUE)
        {
            /* Return the error code */
            return (WORD)GetLastError();
        }
    }

    DescriptorId = DosFindFreeDescriptor();
    if (DescriptorId == 0xFF)
    {
        /* Close the file and return the error code */
        CloseHandle(FileHandle);
        return ERROR_TOO_MANY_OPEN_FILES;
    }

    /* Set up the new descriptor */
    Descriptor = DosGetFileDescriptor(DescriptorId);
    RtlZeroMemory(Descriptor, sizeof(*Descriptor));
    RtlFillMemory(Descriptor->FileName, sizeof(Descriptor->FileName), ' ');

    if (Node != NULL)
    {
        Descriptor->DevicePointer = Node->Driver;
        Descriptor->DeviceInfo = Node->DeviceAttributes | FILE_INFO_DEVICE;
        RtlCopyMemory(Descriptor->FileName, Node->Name.Buffer, Node->Name.Length);
    }
    else
    {
        Descriptor->OpenMode = AccessShareModes;
        Descriptor->Attributes = LOBYTE(GetFileAttributesA(FilePath));
        Descriptor->Size = GetFileSize(FileHandle, NULL);
        Descriptor->Win32Handle = FileHandle;
        StoreNameInSft(FilePath, Descriptor);
    }

    Descriptor->OwnerPsp = Sda->CurrentPsp;

    /* Open the DOS handle */
    DosHandle = DosOpenHandle(DescriptorId);
    if (DosHandle == INVALID_DOS_HANDLE)
    {
        /* Close the file and return the error code */
        CloseHandle(FileHandle);
        return ERROR_TOO_MANY_OPEN_FILES;
    }

    /* It was successful */
    *Handle = DosHandle;
    return ERROR_SUCCESS;
}