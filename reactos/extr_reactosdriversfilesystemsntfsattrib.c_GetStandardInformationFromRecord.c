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
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_5__ {scalar_t__ ValueOffset; } ;
struct TYPE_6__ {scalar_t__ Type; TYPE_1__ Resident; } ;
typedef  int /*<<< orphan*/ * PSTANDARD_INFORMATION ;
typedef  TYPE_2__* PNTFS_ATTR_RECORD ;
typedef  int /*<<< orphan*/  PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FIND_ATTR_CONTXT ;

/* Variables and functions */
 scalar_t__ AttributeStandardInformation ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FindCloseAttribute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FindFirstAttribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  FindNextAttribute (int /*<<< orphan*/ *,TYPE_2__**) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 

PSTANDARD_INFORMATION
GetStandardInformationFromRecord(PDEVICE_EXTENSION Vcb,
                                 PFILE_RECORD_HEADER FileRecord)
{
    NTSTATUS Status;
    FIND_ATTR_CONTXT Context;
    PNTFS_ATTR_RECORD Attribute;
    PSTANDARD_INFORMATION StdInfo;

    Status = FindFirstAttribute(&Context, Vcb, FileRecord, FALSE, &Attribute);
    while (NT_SUCCESS(Status))
    {
        if (Attribute->Type == AttributeStandardInformation)
        {
            StdInfo = (PSTANDARD_INFORMATION)((ULONG_PTR)Attribute + Attribute->Resident.ValueOffset);
            FindCloseAttribute(&Context);
            return StdInfo;
        }

        Status = FindNextAttribute(&Context, &Attribute);
    }

    FindCloseAttribute(&Context);
    return NULL;
}