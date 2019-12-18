#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_8__ {int LargePageMinimum; } ;
struct TYPE_6__ {int QuadPart; } ;
struct TYPE_7__ {TYPE_1__ EndOfFile; } ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  TYPE_2__ FILE_STANDARD_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_SECTION (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_1__,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileStandardInformation ; 
 int /*<<< orphan*/  IGNORE ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int OBJ_CASE_INSENSITIVE ; 
 int OBJ_KERNEL_HANDLE ; 
 int PAGE_EXECUTE_READ ; 
 int PAGE_EXECUTE_READWRITE ; 
 int PAGE_EXECUTE_WRITECOPY ; 
 int PAGE_READONLY ; 
 int PAGE_READWRITE ; 
 int PAGE_WRITECOPY ; 
 int /*<<< orphan*/  RTL_CONSTANT_STRING (char*) ; 
 int SECTION_ALL_ACCESS ; 
 int SECTION_MAP_EXECUTE ; 
 int SECTION_MAP_READ ; 
 int SECTION_MAP_WRITE ; 
 int SEC_COMMIT ; 
 int SEC_IMAGE ; 
 int SEC_LARGE_PAGES ; 
 int SEC_NOCACHE ; 
 int SEC_RESERVE ; 
 int /*<<< orphan*/  STATUS_INVALID_FILE_FOR_SECTION ; 
 int /*<<< orphan*/  STATUS_INVALID_IMAGE_NOT_MZ ; 
 int /*<<< orphan*/  STATUS_INVALID_PAGE_PROTECTION ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER_4 ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER_6 ; 
 int /*<<< orphan*/  STATUS_OBJECT_PATH_SYNTAX_BAD ; 
 int /*<<< orphan*/  STATUS_SECTION_TOO_BIG ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 TYPE_4__* SharedUserData ; 
 int TestStringSize ; 
 int /*<<< orphan*/  ZwQueryInformationFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int _4mb ; 
 int /*<<< orphan*/  skip (int,char*) ; 

__attribute__((used)) static
VOID
SimpleErrorChecks(HANDLE FileHandleReadOnly, HANDLE FileHandleWriteOnly, HANDLE FileHandleExecuteOnly)
{
    NTSTATUS Status;
    HANDLE Section = NULL;
    OBJECT_ATTRIBUTES ObjectAttributesReadOnly;
    OBJECT_ATTRIBUTES ObjectAttributesWriteOnly;
    OBJECT_ATTRIBUTES InvalidObjectAttributes;
    IO_STATUS_BLOCK IoStatusBlock;
    FILE_STANDARD_INFORMATION FileStandardInfo;
    LARGE_INTEGER MaximumSize;
    UNICODE_STRING SectReadOnly = RTL_CONSTANT_STRING(L"\\BaseNamedObjects\\KmtTestReadSect");
    UNICODE_STRING SectWriteOnly = RTL_CONSTANT_STRING(L"\\BaseNamedObjects\\KmtTestWriteSect");
    UNICODE_STRING InvalidObjectString = RTL_CONSTANT_STRING(L"THIS/IS/INVALID");

    MaximumSize.QuadPart = TestStringSize;

    InitializeObjectAttributes(&ObjectAttributesReadOnly, &SectReadOnly, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);
    InitializeObjectAttributes(&ObjectAttributesWriteOnly, &SectWriteOnly, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);
    InitializeObjectAttributes(&InvalidObjectAttributes, &InvalidObjectString, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

    ///////////////////////////////////////////////////////////////////////////////////////
    //PAGE FILE BACKED SECTION
    //DESIRED ACCESS TESTS
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, NULL, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, 0, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, NULL, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, -1, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, NULL, STATUS_SUCCESS, STATUS_SUCCESS);

    //OBJECT ATTRIBUTES
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, &ObjectAttributesReadOnly, MaximumSize, PAGE_READWRITE, SEC_COMMIT, NULL, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, &InvalidObjectAttributes, MaximumSize, PAGE_READWRITE, SEC_COMMIT, NULL, STATUS_OBJECT_PATH_SYNTAX_BAD, STATUS_SUCCESS);

    //MAXIMUM SIZE
    MaximumSize.QuadPart = -1;
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, NULL, STATUS_SECTION_TOO_BIG, IGNORE);

    MaximumSize.QuadPart = 0;
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, SEC_COMMIT, NULL, STATUS_INVALID_PARAMETER_4, IGNORE);

    //division by zero in ROS
    if (!skip(SharedUserData->LargePageMinimum > 0, "LargePageMinimum is 0\n"))
    {
        MaximumSize.QuadPart = (_4mb / SharedUserData->LargePageMinimum) * SharedUserData->LargePageMinimum; //4mb
        CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, (SEC_LARGE_PAGES | SEC_COMMIT), NULL, STATUS_SUCCESS, STATUS_SUCCESS);
    }

    MaximumSize.QuadPart = TestStringSize;

    //SECTION PAGE PROTECTION
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_EXECUTE_READ, SEC_COMMIT, NULL, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_EXECUTE_READWRITE, SEC_COMMIT, NULL, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_EXECUTE_WRITECOPY, SEC_COMMIT, NULL, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, NULL, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, (PAGE_EXECUTE_READ | PAGE_READWRITE), SEC_COMMIT, NULL, STATUS_INVALID_PAGE_PROTECTION, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, (PAGE_READONLY | PAGE_READWRITE), SEC_COMMIT, NULL, STATUS_INVALID_PAGE_PROTECTION, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, (PAGE_WRITECOPY | PAGE_READONLY), SEC_COMMIT, NULL, STATUS_INVALID_PAGE_PROTECTION, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, 0, SEC_COMMIT, NULL, STATUS_INVALID_PAGE_PROTECTION, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, -1, SEC_COMMIT, NULL, STATUS_INVALID_PAGE_PROTECTION, STATUS_SUCCESS);

    //ALLOCATION ATTRIBUTES
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, 0, NULL, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, (SEC_COMMIT | SEC_RESERVE), NULL, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, SEC_RESERVE, NULL, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, SEC_IMAGE, NULL, STATUS_INVALID_FILE_FOR_SECTION, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, (SEC_IMAGE | SEC_COMMIT), NULL, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, -1, NULL, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, SEC_LARGE_PAGES, NULL, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, (SEC_LARGE_PAGES | SEC_COMMIT), NULL, STATUS_INVALID_PARAMETER_4, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, SEC_NOCACHE, NULL, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, (SEC_NOCACHE | SEC_RESERVE | SEC_COMMIT), NULL, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, (SEC_NOCACHE | SEC_COMMIT), NULL, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, (SEC_NOCACHE | SEC_RESERVE), NULL, STATUS_SUCCESS, STATUS_SUCCESS);

    /////////////////////////////////////////////////////////////////////////////////////////////
    //NORMAL FILE-BACKED SECTION

    //DESIRED ACCESS TESTS
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, &ObjectAttributesReadOnly, MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleReadOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, &ObjectAttributesWriteOnly, MaximumSize, PAGE_WRITECOPY, SEC_COMMIT, FileHandleWriteOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_MAP_WRITE, &ObjectAttributesReadOnly, MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleReadOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_MAP_READ, &ObjectAttributesWriteOnly, MaximumSize, PAGE_WRITECOPY, SEC_COMMIT, FileHandleWriteOnly, STATUS_SUCCESS, STATUS_SUCCESS);

    //Object Attributes
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleReadOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, &InvalidObjectAttributes, MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleReadOnly, STATUS_OBJECT_PATH_SYNTAX_BAD, IGNORE);

    //MAXIMUM SIZE
    MaximumSize.QuadPart = TestStringSize - 100;
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleWriteOnly, STATUS_SUCCESS, STATUS_SUCCESS);

    MaximumSize.QuadPart = -1;
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleWriteOnly, STATUS_SECTION_TOO_BIG, IGNORE);

    MaximumSize.QuadPart = TestStringSize + 1;
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleWriteOnly, STATUS_SECTION_TOO_BIG, IGNORE);

    MaximumSize.QuadPart = 0;
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleWriteOnly, STATUS_SUCCESS, STATUS_SUCCESS);

    //SECTION PAGE PROTECTION
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_EXECUTE_READ, SEC_COMMIT, FileHandleWriteOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_EXECUTE_READWRITE, SEC_COMMIT, FileHandleWriteOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_EXECUTE_WRITECOPY, SEC_COMMIT, FileHandleWriteOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleWriteOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, (PAGE_EXECUTE_READ | PAGE_READWRITE), SEC_COMMIT, FileHandleWriteOnly, STATUS_INVALID_PAGE_PROTECTION, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, (PAGE_READONLY | PAGE_READWRITE), SEC_COMMIT, FileHandleWriteOnly, STATUS_INVALID_PAGE_PROTECTION, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, (PAGE_WRITECOPY | PAGE_READONLY), SEC_COMMIT, FileHandleWriteOnly, STATUS_INVALID_PAGE_PROTECTION, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, 0, SEC_COMMIT, FileHandleWriteOnly, STATUS_INVALID_PAGE_PROTECTION, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, -1, SEC_COMMIT, FileHandleWriteOnly, STATUS_INVALID_PAGE_PROTECTION, STATUS_SUCCESS);

    //allocation type
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, 0, FileHandleWriteOnly, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, (SEC_COMMIT | SEC_RESERVE), FileHandleWriteOnly, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, SEC_RESERVE, FileHandleWriteOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, (SEC_IMAGE | SEC_COMMIT), FileHandleWriteOnly, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, -1, FileHandleWriteOnly, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, SEC_LARGE_PAGES, FileHandleWriteOnly, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, (SEC_LARGE_PAGES | SEC_COMMIT), FileHandleWriteOnly, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, SEC_NOCACHE, FileHandleWriteOnly, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, (SEC_NOCACHE | SEC_RESERVE | SEC_COMMIT), FileHandleWriteOnly, STATUS_INVALID_PARAMETER_6, IGNORE);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, (SEC_NOCACHE | SEC_COMMIT), FileHandleWriteOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, (SEC_NOCACHE | SEC_RESERVE), FileHandleWriteOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READWRITE, SEC_IMAGE, FileHandleWriteOnly, STATUS_INVALID_IMAGE_NOT_MZ, IGNORE);

    //////////////////////////////////////////////////
    //EXECUTABLE IMAGE
    CREATE_SECTION(Section, SECTION_MAP_READ, &ObjectAttributesWriteOnly, MaximumSize, PAGE_WRITECOPY, SEC_IMAGE, FileHandleExecuteOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_MAP_EXECUTE, &ObjectAttributesWriteOnly, MaximumSize, PAGE_WRITECOPY, SEC_IMAGE, FileHandleExecuteOnly, STATUS_SUCCESS, STATUS_SUCCESS);

    //DESIRED ACCESS TESTS
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, &ObjectAttributesReadOnly, MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleExecuteOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, &ObjectAttributesWriteOnly, MaximumSize, PAGE_WRITECOPY, SEC_COMMIT, FileHandleExecuteOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_MAP_WRITE, &ObjectAttributesReadOnly, MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleExecuteOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_MAP_READ, &ObjectAttributesWriteOnly, MaximumSize, PAGE_WRITECOPY, SEC_COMMIT, FileHandleExecuteOnly, STATUS_SUCCESS, STATUS_SUCCESS);

    //Object Attributes
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleExecuteOnly, STATUS_SUCCESS, STATUS_SUCCESS);
    CREATE_SECTION(Section, SECTION_ALL_ACCESS, &InvalidObjectAttributes, MaximumSize, PAGE_READONLY, SEC_COMMIT, FileHandleExecuteOnly, STATUS_OBJECT_PATH_SYNTAX_BAD, IGNORE);

    //MaximumSize
    Status = ZwQueryInformationFile(FileHandleExecuteOnly, &IoStatusBlock, &FileStandardInfo, sizeof(FILE_STANDARD_INFORMATION), FileStandardInformation);
    if (!skip(NT_SUCCESS(Status), "Cannot query file information\n"))
    {
        //as big as file
        MaximumSize = FileStandardInfo.EndOfFile;
        CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_EXECUTE_READ, SEC_IMAGE, FileHandleExecuteOnly, STATUS_SUCCESS, STATUS_SUCCESS);

        //less than file
        MaximumSize.QuadPart = FileStandardInfo.EndOfFile.QuadPart - 2;
        CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_EXECUTE_READ, SEC_IMAGE, FileHandleExecuteOnly, STATUS_SUCCESS, STATUS_SUCCESS);

        //larger than file
        MaximumSize.QuadPart = FileStandardInfo.EndOfFile.QuadPart + 2;
        CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_EXECUTE_READ, SEC_IMAGE, FileHandleExecuteOnly, STATUS_SUCCESS, STATUS_SUCCESS);

        //0
        MaximumSize.QuadPart = 0;
        CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_EXECUTE_READ, SEC_IMAGE, FileHandleExecuteOnly, STATUS_SUCCESS, STATUS_SUCCESS);

        //-1 (very big number)
        MaximumSize.QuadPart = -1;
        CREATE_SECTION(Section, SECTION_ALL_ACCESS, NULL, MaximumSize, PAGE_EXECUTE_READ, SEC_IMAGE, FileHandleExecuteOnly, STATUS_SECTION_TOO_BIG, IGNORE);
    }
}