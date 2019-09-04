#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int FileAttributes; int /*<<< orphan*/  LastWriteTime; int /*<<< orphan*/  ChangeTime; int /*<<< orphan*/  LastAccessTime; int /*<<< orphan*/  CreationTime; } ;
struct TYPE_9__ {int /*<<< orphan*/  UpdateTime; int /*<<< orphan*/  UpdateDate; int /*<<< orphan*/  AccessDate; int /*<<< orphan*/  CreationTime; int /*<<< orphan*/  CreationDate; } ;
struct TYPE_8__ {int /*<<< orphan*/  UpdateTime; int /*<<< orphan*/  UpdateDate; int /*<<< orphan*/  AccessTime; int /*<<< orphan*/  AccessDate; int /*<<< orphan*/  CreationTime; int /*<<< orphan*/  CreationDate; } ;
struct TYPE_10__ {TYPE_2__ Fat; TYPE_1__ FatX; } ;
struct TYPE_11__ {int* Attributes; TYPE_3__ entry; } ;
typedef  TYPE_4__* PVFATFCB ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  TYPE_5__* PFILE_BASIC_INFORMATION ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FILE_BASIC_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int FILE_ATTRIBUTE_ARCHIVE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_HIDDEN ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int FILE_ATTRIBUTE_SYSTEM ; 
 int /*<<< orphan*/  FsdDosDateTimeToSystemTime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int /*<<< orphan*/ ) ; 
 scalar_t__ vfatVolumeIsFatX (int /*<<< orphan*/ ) ; 

NTSTATUS
VfatGetBasicInformation(
    PFILE_OBJECT FileObject,
    PVFATFCB FCB,
    PDEVICE_EXTENSION DeviceExt,
    PFILE_BASIC_INFORMATION BasicInfo,
    PULONG BufferLength)
{
    UNREFERENCED_PARAMETER(FileObject);

    DPRINT("VfatGetBasicInformation()\n");

    if (*BufferLength < sizeof(FILE_BASIC_INFORMATION))
        return STATUS_BUFFER_OVERFLOW;

    if (vfatVolumeIsFatX(DeviceExt))
    {
        FsdDosDateTimeToSystemTime(DeviceExt,
                                   FCB->entry.FatX.CreationDate,
                                   FCB->entry.FatX.CreationTime,
                                   &BasicInfo->CreationTime);
        FsdDosDateTimeToSystemTime(DeviceExt,
                                   FCB->entry.FatX.AccessDate,
                                   FCB->entry.FatX.AccessTime,
                                   &BasicInfo->LastAccessTime);
        FsdDosDateTimeToSystemTime(DeviceExt,
                                   FCB->entry.FatX.UpdateDate,
                                   FCB->entry.FatX.UpdateTime,
                                   &BasicInfo->LastWriteTime);
        BasicInfo->ChangeTime = BasicInfo->LastWriteTime;
    }
    else
    {
        FsdDosDateTimeToSystemTime(DeviceExt,
                                   FCB->entry.Fat.CreationDate,
                                   FCB->entry.Fat.CreationTime,
                                   &BasicInfo->CreationTime);
        FsdDosDateTimeToSystemTime(DeviceExt,
                                   FCB->entry.Fat.AccessDate,
                                   0,
                                   &BasicInfo->LastAccessTime);
        FsdDosDateTimeToSystemTime(DeviceExt,
                                   FCB->entry.Fat.UpdateDate,
                                   FCB->entry.Fat.UpdateTime,
                                   &BasicInfo->LastWriteTime);
        BasicInfo->ChangeTime = BasicInfo->LastWriteTime;
    }

    BasicInfo->FileAttributes = *FCB->Attributes & 0x3f;
    /* Synthesize FILE_ATTRIBUTE_NORMAL */
    if (0 == (BasicInfo->FileAttributes & (FILE_ATTRIBUTE_DIRECTORY |
                                           FILE_ATTRIBUTE_ARCHIVE |
                                           FILE_ATTRIBUTE_SYSTEM |
                                           FILE_ATTRIBUTE_HIDDEN |
                                           FILE_ATTRIBUTE_READONLY)))
    {
        DPRINT("Synthesizing FILE_ATTRIBUTE_NORMAL\n");
        BasicInfo->FileAttributes |= FILE_ATTRIBUTE_NORMAL;
    }
    DPRINT("Getting attributes 0x%02x\n", BasicInfo->FileAttributes);

    *BufferLength -= sizeof(FILE_BASIC_INFORMATION);
    return STATUS_SUCCESS;
}