#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ UCHAR ;
struct TYPE_9__ {scalar_t__ NameType; } ;
struct TYPE_7__ {scalar_t__ ValueOffset; } ;
struct TYPE_8__ {scalar_t__ Type; TYPE_1__ Resident; } ;
typedef  TYPE_2__* PNTFS_ATTR_RECORD ;
typedef  int /*<<< orphan*/  PFILE_RECORD_HEADER ;
typedef  TYPE_3__* PFILENAME_ATTRIBUTE ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FIND_ATTR_CONTXT ;

/* Variables and functions */
 scalar_t__ AttributeFileName ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FindCloseAttribute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FindFirstAttribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  FindNextAttribute (int /*<<< orphan*/ *,TYPE_2__**) ; 
 scalar_t__ NTFS_FILE_NAME_DOS ; 
 scalar_t__ NTFS_FILE_NAME_WIN32 ; 
 scalar_t__ NTFS_FILE_NAME_WIN32_AND_DOS ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 

PFILENAME_ATTRIBUTE
GetFileNameFromRecord(PDEVICE_EXTENSION Vcb,
                      PFILE_RECORD_HEADER FileRecord,
                      UCHAR NameType)
{
    FIND_ATTR_CONTXT Context;
    PNTFS_ATTR_RECORD Attribute;
    PFILENAME_ATTRIBUTE Name;
    NTSTATUS Status;

    Status = FindFirstAttribute(&Context, Vcb, FileRecord, FALSE, &Attribute);
    while (NT_SUCCESS(Status))
    {
        if (Attribute->Type == AttributeFileName)
        {
            Name = (PFILENAME_ATTRIBUTE)((ULONG_PTR)Attribute + Attribute->Resident.ValueOffset);
            if (Name->NameType == NameType ||
                (Name->NameType == NTFS_FILE_NAME_WIN32_AND_DOS && NameType == NTFS_FILE_NAME_WIN32) ||
                (Name->NameType == NTFS_FILE_NAME_WIN32_AND_DOS && NameType == NTFS_FILE_NAME_DOS))
            {
                FindCloseAttribute(&Context);
                return Name;
            }
        }

        Status = FindNextAttribute(&Context, &Attribute);
    }

    FindCloseAttribute(&Context);
    return NULL;
}