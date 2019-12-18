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
typedef  int /*<<< orphan*/  USHORT ;
struct TYPE_6__ {int DataIsDirectory; scalar_t__ OffsetToData; scalar_t__ NameIsString; int /*<<< orphan*/  Name; } ;
struct TYPE_5__ {TYPE_2__* Lang1Entries; } ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_1__* PTEST_RESOURCES ;
typedef  TYPE_2__* PIMAGE_RESOURCE_DIRECTORY_ENTRY ;

/* Variables and functions */

__attribute__((used)) static
VOID
InitializeIdEntry(
    PTEST_RESOURCES Resource,
    PIMAGE_RESOURCE_DIRECTORY_ENTRY DirEntry,
    USHORT Id,
    PVOID Data)
{
    DirEntry->Name = Id;
    DirEntry->NameIsString = 0;
    DirEntry->OffsetToData = (PUCHAR)Data - (PUCHAR)Resource;
    if (DirEntry < Resource->Lang1Entries)
        DirEntry->DataIsDirectory = 1;
}