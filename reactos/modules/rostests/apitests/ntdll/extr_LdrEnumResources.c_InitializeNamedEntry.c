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
struct TYPE_6__ {int NameIsString; int DataIsDirectory; scalar_t__ OffsetToData; scalar_t__ Name; } ;
struct TYPE_5__ {int StringIndex; int* StringBuffer; TYPE_2__* Lang1Entries; } ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_1__* PTEST_RESOURCES ;
typedef  TYPE_2__* PIMAGE_RESOURCE_DIRECTORY_ENTRY ;

/* Variables and functions */
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringBuffer ; 
 int /*<<< orphan*/  TEST_RESOURCES ; 
 int /*<<< orphan*/  wcscpy (int*,int /*<<< orphan*/ ) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
VOID
InitializeNamedEntry(
    PTEST_RESOURCES Resource,
    PIMAGE_RESOURCE_DIRECTORY_ENTRY DirEntry,
    PWCHAR Name,
    PVOID Data)
{
    DirEntry->Name = Resource->StringIndex * 2 + FIELD_OFFSET(TEST_RESOURCES, StringBuffer);
    DirEntry->NameIsString = 1;
    DirEntry->OffsetToData = (PUCHAR)Data - (PUCHAR)Resource;
    if (DirEntry < Resource->Lang1Entries)
        DirEntry->DataIsDirectory = 1;
    Resource->StringBuffer[Resource->StringIndex] = wcslen(Name);
    wcscpy(&Resource->StringBuffer[Resource->StringIndex + 1], Name);
    Resource->StringIndex += Resource->StringBuffer[Resource->StringIndex] * 2 + 1;
}