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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  PNTFS_ATTR_RECORD ;
typedef  int /*<<< orphan*/  PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FIND_ATTR_CONTXT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FindCloseAttribute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FindFirstAttribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FindNextAttribute (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsDumpAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID
NtfsDumpFileAttributes(PDEVICE_EXTENSION Vcb,
                       PFILE_RECORD_HEADER FileRecord)
{
    NTSTATUS Status;
    FIND_ATTR_CONTXT Context;
    PNTFS_ATTR_RECORD Attribute;

    Status = FindFirstAttribute(&Context, Vcb, FileRecord, FALSE, &Attribute);
    while (NT_SUCCESS(Status))
    {
        NtfsDumpAttribute(Vcb, Attribute);

        Status = FindNextAttribute(&Context, &Attribute);
    }

    FindCloseAttribute(&Context);
}