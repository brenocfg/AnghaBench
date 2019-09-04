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
struct TYPE_6__ {void* QuadPart; } ;
struct TYPE_5__ {int /*<<< orphan*/ * SectionObjectPointer; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * PSECTION_OBJECT_POINTERS ;
typedef  TYPE_1__* PFILE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_SECTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckObject (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  CheckSection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IGNORE ; 
 int /*<<< orphan*/ * IoFileObjectType ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  NO_HANDLE_CLOSE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObDereferenceObject (TYPE_1__*) ; 
 int /*<<< orphan*/  ObReferenceObjectByHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  SECTION_ALL_ACCESS ; 
 int /*<<< orphan*/  SEC_COMMIT ; 
 int /*<<< orphan*/  SEC_FILE ; 
 int /*<<< orphan*/  STANDARD_RIGHTS_ALL ; 
 int /*<<< orphan*/  STATUS_INVALID_FILE_FOR_SECTION ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 void* TestStringSize ; 
 int /*<<< orphan*/  ZwClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static
VOID
BasicBehaviorChecks(HANDLE FileHandle)
{
    NTSTATUS Status;
    HANDLE Section = NULL;
    PFILE_OBJECT FileObject;
    LARGE_INTEGER Length;
    Length.QuadPart = TestStringSize;

    //mimic lack of section support for a particular file as well.
    Status = ObReferenceObjectByHandle(FileHandle, STANDARD_RIGHTS_ALL, *IoFileObjectType, KernelMode, (PVOID *)&FileObject, NULL);
    if (!skip(NT_SUCCESS(Status), "Cannot reference object by handle\n"))
    {
        PSECTION_OBJECT_POINTERS Pointers = FileObject->SectionObjectPointer;

        FileObject->SectionObjectPointer = NULL;
        CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, Length, PAGE_READONLY, SEC_COMMIT, FileHandle, STATUS_INVALID_FILE_FOR_SECTION, IGNORE);
        FileObject->SectionObjectPointer = Pointers;
        ObDereferenceObject(FileObject);
    }

    Length.QuadPart = TestStringSize;
    CREATE_SECTION(Section, (SECTION_ALL_ACCESS), NULL, Length, PAGE_READONLY, SEC_COMMIT, FileHandle, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    CheckObject(Section, 2, 1);
    CheckSection(Section, SEC_FILE, Length.QuadPart, STATUS_SUCCESS);
    ZwClose(Section); //manually close it due to NO_HANDLE_CLOSE in CREATE_SECTION

    //section length should be set to that of file
    Length.QuadPart = 0;
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, Length, PAGE_READONLY, SEC_COMMIT, FileHandle, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    CheckSection(Section, SEC_FILE, TestStringSize, STATUS_SUCCESS);
    ZwClose(Section);

    //create a smaller section than file
    Length.QuadPart = TestStringSize - 100;
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, Length, PAGE_READONLY, SEC_COMMIT, FileHandle, STATUS_SUCCESS, NO_HANDLE_CLOSE);
    CheckSection(Section, SEC_FILE, TestStringSize - 100, STATUS_SUCCESS);
    ZwClose(Section);
}