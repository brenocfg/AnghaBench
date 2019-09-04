#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  NameInformation; int /*<<< orphan*/  PositionInformation; int /*<<< orphan*/  EaInformation; int /*<<< orphan*/  InternalInformation; int /*<<< orphan*/  StandardInformation; int /*<<< orphan*/  BasicInformation; } ;
struct TYPE_13__ {int /*<<< orphan*/  FileName; } ;
typedef  TYPE_1__* PVFATFCB ;
typedef  scalar_t__* PULONG ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  TYPE_1__* PFILE_ALL_INFORMATION ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FILE_MODE_INFORMATION ;
typedef  int /*<<< orphan*/  FILE_ALIGNMENT_INFORMATION ;
typedef  int /*<<< orphan*/  FILE_ACCESS_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_1__*) ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_ALL_INFORMATION ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 TYPE_11__ NameInformation ; 
 int /*<<< orphan*/  STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  VfatGetBasicInformation (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  VfatGetEaInformation (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  VfatGetInternalInformation (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  VfatGetNameInformation (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  VfatGetPositionInformation (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  VfatGetStandardInformation (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static
NTSTATUS
VfatGetAllInformation(
    PFILE_OBJECT FileObject,
    PVFATFCB Fcb,
    PDEVICE_EXTENSION DeviceExt,
    PFILE_ALL_INFORMATION Info,
    PULONG BufferLength)
{
    NTSTATUS Status;

    ASSERT(Info);
    ASSERT(Fcb);

    if (*BufferLength < FIELD_OFFSET(FILE_ALL_INFORMATION, NameInformation.FileName))
        return STATUS_BUFFER_OVERFLOW;

    *BufferLength -= (sizeof(FILE_ACCESS_INFORMATION) + sizeof(FILE_MODE_INFORMATION) + sizeof(FILE_ALIGNMENT_INFORMATION));

    /* Basic Information */
    Status = VfatGetBasicInformation(FileObject, Fcb, DeviceExt, &Info->BasicInformation, BufferLength);
    if (!NT_SUCCESS(Status)) return Status;
    /* Standard Information */
    Status = VfatGetStandardInformation(Fcb, &Info->StandardInformation, BufferLength);
    if (!NT_SUCCESS(Status)) return Status;
    /* Internal Information */
    Status = VfatGetInternalInformation(Fcb, DeviceExt, &Info->InternalInformation, BufferLength);
    if (!NT_SUCCESS(Status)) return Status;
    /* EA Information */
    Status = VfatGetEaInformation(FileObject, Fcb, DeviceExt, &Info->EaInformation, BufferLength);
    if (!NT_SUCCESS(Status)) return Status;
    /* Position Information */
    Status = VfatGetPositionInformation(FileObject, Fcb, DeviceExt, &Info->PositionInformation, BufferLength);
    if (!NT_SUCCESS(Status)) return Status;
    /* Name Information */
    Status = VfatGetNameInformation(FileObject, Fcb, DeviceExt, &Info->NameInformation, BufferLength);

    return Status;
}