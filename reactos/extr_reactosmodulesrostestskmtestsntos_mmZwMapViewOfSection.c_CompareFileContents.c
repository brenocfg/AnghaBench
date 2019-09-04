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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  Information; } ;
struct TYPE_5__ {scalar_t__ QuadPart; } ;
typedef  scalar_t__ SIZE_T ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  TYPE_2__ IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * ExAllocatePoolWithTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  PagedPool ; 
 scalar_t__ RtlCompareMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  ZwReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok_eq_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_eq_ulongptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static
SIZE_T
CompareFileContents(HANDLE FileHandle, ULONG BufferLength, PVOID Buffer)
{
    NTSTATUS Status;
    LARGE_INTEGER ByteOffset;
    IO_STATUS_BLOCK IoStatusBlock;
    PVOID FileContent;
    SIZE_T Match;

    Match = 0;
    ByteOffset.QuadPart = 0;

    FileContent = ExAllocatePoolWithTag(PagedPool, BufferLength, 'Test');
    if (!skip((FileContent != NULL), "Error allocating memory for FileContent\n"))
    {
        Status = ZwReadFile(FileHandle, NULL, NULL, NULL, &IoStatusBlock, FileContent, BufferLength, &ByteOffset, NULL);
        ok_eq_hex(Status, STATUS_SUCCESS);
        ok_eq_ulongptr(IoStatusBlock.Information, BufferLength);

        Match = 0;
        Match = RtlCompareMemory(FileContent, Buffer, BufferLength);
        ExFreePoolWithTag(FileContent, 'Test');
    }

    return Match;
}