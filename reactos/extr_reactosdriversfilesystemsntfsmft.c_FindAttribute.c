#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
struct TYPE_18__ {int /*<<< orphan*/  Offset; } ;
struct TYPE_17__ {int /*<<< orphan*/  MFTRecordNumber; } ;
struct TYPE_16__ {int /*<<< orphan*/  FileMFTIndex; } ;
struct TYPE_15__ {scalar_t__ Type; scalar_t__ NameLength; scalar_t__ NameOffset; } ;
typedef  scalar_t__ PWCHAR ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  TYPE_1__* PNTFS_ATTR_RECORD ;
typedef  TYPE_2__* PNTFS_ATTR_CONTEXT ;
typedef  TYPE_3__* PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  scalar_t__ PCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_4__ FIND_ATTR_CONTXT ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FindCloseAttribute (TYPE_4__*) ; 
 int /*<<< orphan*/  FindFirstAttribute (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,TYPE_1__**) ; 
 int /*<<< orphan*/  FindNextAttribute (TYPE_4__*,TYPE_1__**) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 TYPE_2__* PrepareAttributeContext (TYPE_1__*) ; 
 scalar_t__ RtlCompareMemory (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_OBJECT_NAME_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ TRUE ; 

NTSTATUS
FindAttribute(PDEVICE_EXTENSION Vcb,
              PFILE_RECORD_HEADER MftRecord,
              ULONG Type,
              PCWSTR Name,
              ULONG NameLength,
              PNTFS_ATTR_CONTEXT * AttrCtx,
              PULONG Offset)
{
    BOOLEAN Found;
    NTSTATUS Status;
    FIND_ATTR_CONTXT Context;
    PNTFS_ATTR_RECORD Attribute;

    DPRINT("FindAttribute(%p, %p, 0x%x, %S, %lu, %p, %p)\n", Vcb, MftRecord, Type, Name, NameLength, AttrCtx, Offset);

    Found = FALSE;
    Status = FindFirstAttribute(&Context, Vcb, MftRecord, FALSE, &Attribute);
    while (NT_SUCCESS(Status))
    {
        if (Attribute->Type == Type && Attribute->NameLength == NameLength)
        {
            if (NameLength != 0)
            {
                PWCHAR AttrName;

                AttrName = (PWCHAR)((PCHAR)Attribute + Attribute->NameOffset);
                DPRINT("%.*S, %.*S\n", Attribute->NameLength, AttrName, NameLength, Name);
                if (RtlCompareMemory(AttrName, Name, NameLength * sizeof(WCHAR)) == (NameLength  * sizeof(WCHAR)))
                {
                    Found = TRUE;
                }
            }
            else
            {
                Found = TRUE;
            }

            if (Found)
            {
                /* Found it, fill up the context and return. */
                DPRINT("Found context\n");
                *AttrCtx = PrepareAttributeContext(Attribute);

                (*AttrCtx)->FileMFTIndex = MftRecord->MFTRecordNumber;

                if (Offset != NULL)
                    *Offset = Context.Offset;

                FindCloseAttribute(&Context);
                return STATUS_SUCCESS;
            }
        }

        Status = FindNextAttribute(&Context, &Attribute);
    }

    FindCloseAttribute(&Context);
    return STATUS_OBJECT_NAME_NOT_FOUND;
}