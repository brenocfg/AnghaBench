#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {int QuadPart; } ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  scalar_t__ PCHAR ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  FILE_SYNCHRONOUS_IO_NONALERT ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MEM_COMMIT ; 
 int MEM_RESERVE ; 
 int /*<<< orphan*/  NtAllocateVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCreateSection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtMapViewOfSection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtOpenFile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  RtlDosPathNameToNtPathName_U (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SECTION_ALL_ACCESS ; 
 int /*<<< orphan*/  SEC_IMAGE ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int SYNCHRONIZE ; 
 int /*<<< orphan*/  ViewShare ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok_ntstatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  system (char*) ; 

void
Test_ImageSection2(void)
{
    UNICODE_STRING FileName;
    NTSTATUS Status;
    OBJECT_ATTRIBUTES FileObjectAttributes;
    IO_STATUS_BLOCK IoStatusBlock;
    HANDLE FileHandle, ImageSectionHandle;
    PVOID ImageBase, BaseAddress;
    SIZE_T ViewSize;
    LARGE_INTEGER MaximumSize, SectionOffset;

    if (!RtlDosPathNameToNtPathName_U(L"testdata\\nvoglv32.dll",
                                      &FileName,
                                      NULL,
                                      NULL))
    {
        ok(0, "RtlDosPathNameToNtPathName_U failed\n");
        return;
    }

    InitializeObjectAttributes(&FileObjectAttributes,
                               &FileName,
                               0,
                               NULL,
                               NULL);

    Status = NtOpenFile(&FileHandle,
                        GENERIC_READ|GENERIC_WRITE|SYNCHRONIZE,
                        &FileObjectAttributes,
                        &IoStatusBlock,
                        FILE_SHARE_READ,
                        FILE_SYNCHRONOUS_IO_NONALERT);
    ok_ntstatus(Status, STATUS_SUCCESS);
    printf("Opened file with handle %p\n", FileHandle);

    /* Create a data section with write access */
    MaximumSize.QuadPart = 0x20000;
    Status = NtCreateSection(&ImageSectionHandle,
                             SECTION_ALL_ACCESS, // DesiredAccess
                             NULL, // ObjectAttributes
                             &MaximumSize, // MaximumSize
                             PAGE_READWRITE, // SectionPageProtection
                             SEC_IMAGE, // AllocationAttributes
                             FileHandle);
    ok_ntstatus(Status, STATUS_SUCCESS);

    printf("Created image section with handle %p\n", ImageSectionHandle);
    //system("PAUSE");

    /* Map the image section */
    ImageBase = NULL;
    ViewSize = 0x0000;
    SectionOffset.QuadPart = 0x00000;
    Status = NtMapViewOfSection(ImageSectionHandle,
                                NtCurrentProcess(),
                                &ImageBase,
                                0,
                                0,
                                &SectionOffset,
                                &ViewSize,
                                ViewShare,
                                0,
                                PAGE_READWRITE);
    ok_ntstatus(Status, STATUS_SUCCESS);

    printf("Mapped image section at %p, value in text section: %lx\n",
           ImageBase, *((ULONG*)((PCHAR)ImageBase + 0x1196)));
    system("PAUSE");

    /* Try to allocate a page after the section */
    BaseAddress = (PUCHAR)ImageBase + 0x10000;
    ViewSize = 0x1000;
    Status = NtAllocateVirtualMemory(NtCurrentProcess(),
                                     &BaseAddress,
                                     0,
                                     &ViewSize,
                                     MEM_RESERVE | MEM_COMMIT,
                                     PAGE_READWRITE);
    printf("allocation status: %lx\n", Status);
    system("PAUSE");

}