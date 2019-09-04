#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  TestDllPath ;
typedef  int SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  FILE_SYNCHRONOUS_IO_NONALERT ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MEM_RESERVE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtAllocateVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCreateSection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtCurrentProcess () ; 
 int /*<<< orphan*/  NtFlushVirtualMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtMapViewOfSection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtOpenFile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtUnmapViewOfSection (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_NOACCESS ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  RTL_NUMBER_OF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlDosPathNameToNtPathName_U (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SECTION_ALL_ACCESS ; 
 int /*<<< orphan*/  SEC_COMMIT ; 
 int /*<<< orphan*/  SEC_IMAGE ; 
 int /*<<< orphan*/  STATUS_CONFLICTING_ADDRESSES ; 
 int /*<<< orphan*/  STATUS_IMAGE_MACHINE_TYPE_MISMATCH ; 
 int /*<<< orphan*/  STATUS_INVALID_IMAGE_NOT_MZ ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int SYNCHRONIZE ; 
 int /*<<< orphan*/  StringCbCatW (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  UNICODE_NULL ; 
 int /*<<< orphan*/  ViewShare ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_hex (int,int) ; 
 int /*<<< orphan*/  ok_ntstatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/ * wcsrchr (int /*<<< orphan*/ *,int) ; 

void
Test_ImageSection(void)
{
    UNICODE_STRING FileName;
    NTSTATUS Status;
    OBJECT_ATTRIBUTES FileObjectAttributes;
    IO_STATUS_BLOCK IoStatusBlock;
    WCHAR TestDllPath[MAX_PATH];
    HANDLE FileHandle, DataSectionHandle, ImageSectionHandle;
    PVOID DataBase, ImageBase;
    SIZE_T ViewSize;

    GetModuleFileNameW(NULL, TestDllPath, RTL_NUMBER_OF(TestDllPath));
    wcsrchr(TestDllPath, L'\\')[1] = UNICODE_NULL;
    StringCbCatW(TestDllPath, sizeof(TestDllPath), L"testdata\\test.dll");
    if (!RtlDosPathNameToNtPathName_U(TestDllPath,
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
    if (!NT_SUCCESS(Status))
    {
        skip("Failed to open file\n");
        return;
    }

    /* Create a data section with write access */
    Status = NtCreateSection(&DataSectionHandle,
                             SECTION_ALL_ACCESS, // DesiredAccess
                             NULL, // ObjectAttributes
                             NULL, // MaximumSize
                             PAGE_READWRITE, // SectionPageProtection
                             SEC_COMMIT, // AllocationAttributes
                             FileHandle);
    ok_ntstatus(Status, STATUS_SUCCESS);
    if (!NT_SUCCESS(Status))
    {
        skip("Failed to create data section\n");
        NtClose(FileHandle);
        return;
    }

    /* Map the data section as flat mapping */
    DataBase = NULL;
    ViewSize = 0;
    Status = NtMapViewOfSection(DataSectionHandle,
                                NtCurrentProcess(),
                                &DataBase,
                                0,
                                0,
                                NULL,
                                &ViewSize,
                                ViewShare,
                                0,
                                PAGE_READWRITE);
    ok_ntstatus(Status, STATUS_SUCCESS);
    //ok(ViewSize == 0x3f95cc48, "ViewSize wrong: 0x%lx\n");
    if (!NT_SUCCESS(Status))
    {
        skip("Failed to map view of data section\n");
        NtClose(DataSectionHandle);
        NtClose(FileHandle);
        return;
    }

    /* Check the original data */
    ok(*(ULONG*)DataBase == 0x00905a4d, "Header not ok\n");

    /* Modify the PE header (but do not flush!) */
    *(ULONG*)DataBase = 0xdeadbabe;
    ok(*(ULONG*)DataBase == 0xdeadbabe, "Header not ok\n");

    /* Modify data in the .data section (but do not flush!) */
    ok(*(ULONG*)((PUCHAR)DataBase + 0x800) == 0x12345678,
       "Data in .data section invalid: 0x%lx!\n", *(ULONG*)((PUCHAR)DataBase + 0x800));
    *(ULONG*)((PUCHAR)DataBase + 0x800) = 0x87654321;

    /* Now try to create an image section (should fail) */
    Status = NtCreateSection(&ImageSectionHandle,
                             SECTION_ALL_ACCESS, // DesiredAccess
                             NULL, // ObjectAttributes
                             NULL, // MaximumSize
                             PAGE_READWRITE, // SectionPageProtection
                             SEC_IMAGE, // AllocationAttributes
                             FileHandle);
    ok_ntstatus(Status, STATUS_INVALID_IMAGE_NOT_MZ);
    if (NT_SUCCESS(Status)) NtClose(ImageSectionHandle);

    /* Restore the original header */
    *(ULONG*)DataBase = 0x00905a4d;

    /* Modify data in the .data section (but do not flush!) */
    ok_hex(*(ULONG*)((PUCHAR)DataBase + 0x800), 0x87654321);
    *(ULONG*)((PUCHAR)DataBase + 0x800) = 0xdeadbabe;

    /* Try to create an image section again */
    Status = NtCreateSection(&ImageSectionHandle,
                             SECTION_ALL_ACCESS, // DesiredAccess
                             NULL, // ObjectAttributes
                             NULL, // MaximumSize
                             PAGE_READWRITE, // SectionPageProtection
                             SEC_IMAGE, // AllocationAttributes
                             FileHandle);
    ok_ntstatus(Status, STATUS_SUCCESS);
    if (!NT_SUCCESS(Status))
    {
        skip("Failed to create image section\n");
        NtClose(DataSectionHandle);
        NtClose(FileHandle);
        return;
    }

    /* Map the image section */
    ImageBase = NULL;
    ViewSize = 0;
    Status = NtMapViewOfSection(ImageSectionHandle,
                                NtCurrentProcess(),
                                &ImageBase,
                                0, // ZeroBits
                                0, // CommitSize
                                NULL, // SectionOffset
                                &ViewSize,
                                ViewShare,
                                0, // AllocationType
                                PAGE_READONLY);
#ifdef _M_IX86
    ok_ntstatus(Status, STATUS_SUCCESS);
#else
    ok_ntstatus(Status, STATUS_IMAGE_MACHINE_TYPE_MISMATCH);
#endif
    if (!NT_SUCCESS(Status))
    {
        skip("Failed to map view of image section\n");
        NtClose(ImageSectionHandle);
        NtClose(DataSectionHandle);
        NtClose(FileHandle);
        return;
    }

    /* Check the header */
    ok(*(ULONG*)DataBase == 0x00905a4d, "Header not ok\n");
    ok(*(ULONG*)ImageBase == 0x00905a4d, "Header not ok\n");

    /* Check the data section. Either of these can be present! */
    ok((*(ULONG*)((PUCHAR)ImageBase + 0x80000) == 0x87654321) ||
       (*(ULONG*)((PUCHAR)ImageBase + 0x80000) == 0x12345678),
       "Wrong value in data section: 0x%lx!\n", *(ULONG*)((PUCHAR)ImageBase + 0x80000));

    /* Now modify the data again */
    *(ULONG*)DataBase = 0xdeadbabe;
    *(ULONG*)((PUCHAR)DataBase + 0x800) = 0xf00dada;

    /* Check the data */
    ok(*(ULONG*)DataBase == 0xdeadbabe, "Header not ok\n");
    ok(*(ULONG*)ImageBase == 0x00905a4d, "Data should not be synced!\n");
    ok((*(ULONG*)((PUCHAR)ImageBase + 0x80000) == 0x87654321) ||
       (*(ULONG*)((PUCHAR)ImageBase + 0x80000) == 0x12345678),
       "Wrong value in data section: 0x%lx!\n", *(ULONG*)((PUCHAR)ImageBase + 0x80000));

    /* Flush the view */
    ViewSize = 0x1000;
    Status = NtFlushVirtualMemory(NtCurrentProcess(),
                                  &DataBase,
                                  &ViewSize,
                                  &IoStatusBlock);
    ok_ntstatus(Status, STATUS_SUCCESS);

    /* Check the data again */
    ok(*(ULONG*)ImageBase == 0x00905a4d, "Data should not be synced!\n");
    ok((*(ULONG*)((PUCHAR)ImageBase + 0x80000) == 0x87654321) ||
       (*(ULONG*)((PUCHAR)ImageBase + 0x80000) == 0x12345678),
       "Wrong value in data section: 0x%lx!\n", *(ULONG*)((PUCHAR)ImageBase + 0x80000));

    /* Restore the original header */
    *(ULONG*)DataBase = 0x00905a4d;
    ok(*(ULONG*)DataBase == 0x00905a4d, "Header not ok\n");

    /* Close the image mapping */
    NtUnmapViewOfSection(NtCurrentProcess(), ImageBase);
    NtClose(ImageSectionHandle);

    /* Create an image section again */
    Status = NtCreateSection(&ImageSectionHandle,
                             SECTION_ALL_ACCESS, // DesiredAccess
                             NULL, // ObjectAttributes
                             NULL, // MaximumSize
                             PAGE_READWRITE, // SectionPageProtection
                             SEC_IMAGE, // AllocationAttributes
                             FileHandle);
    ok_ntstatus(Status, STATUS_SUCCESS);
    if (!NT_SUCCESS(Status))
    {
        skip("Failed to create image section\n");
        NtClose(DataSectionHandle);
        NtClose(FileHandle);
        return;
    }

    /* Map the image section again */
    ImageBase = NULL;
    ViewSize = 0;
    Status = NtMapViewOfSection(ImageSectionHandle,
                                NtCurrentProcess(),
                                &ImageBase,
                                0,
                                0,
                                NULL,
                                &ViewSize,
                                ViewShare,
                                0,
                                PAGE_READONLY);
#ifdef _M_IX86
    ok_ntstatus(Status, STATUS_SUCCESS);
#else
    ok_ntstatus(Status, STATUS_IMAGE_MACHINE_TYPE_MISMATCH);
#endif
    if (!NT_SUCCESS(Status))
    {
        skip("Failed to map view of image section\n");
        NtClose(ImageSectionHandle);
        NtClose(DataSectionHandle);
        NtClose(FileHandle);
        return;
    }

    // This one doesn't always work, needs investigation
    /* Check the .data section again */
    //ok(*(ULONG*)((PUCHAR)ImageBase + 0x80000) == 0xf00dada,
    //   "Data should be synced: 0x%lx!\n", *(ULONG*)((PUCHAR)ImageBase + 0x80000));

    /* Restore the original data */
    *(ULONG*)((PUCHAR)DataBase + 0x800) = 0x12345678;

    /* Close the data mapping */
    NtUnmapViewOfSection(NtCurrentProcess(), DataBase);

    NtClose(DataSectionHandle);

    /* Try to allocate memory inside the image mapping */
    DataBase = (PUCHAR)ImageBase + 0x20000;
    ViewSize = 0x1000;
    Status = NtAllocateVirtualMemory(NtCurrentProcess(), &DataBase, 0, &ViewSize, MEM_RESERVE, PAGE_NOACCESS);
    ok_ntstatus(Status, STATUS_CONFLICTING_ADDRESSES);

    /* Cleanup */
    NtClose(FileHandle);
    NtClose(ImageSectionHandle);
    NtUnmapViewOfSection(NtCurrentProcess(), ImageBase);
}