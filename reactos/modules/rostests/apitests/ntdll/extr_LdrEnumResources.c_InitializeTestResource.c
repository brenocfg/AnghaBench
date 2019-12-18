#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {scalar_t__ StringBuffer; int /*<<< orphan*/ * DataEntries; int /*<<< orphan*/ * Lang4Entries; int /*<<< orphan*/  Lang4Directory; int /*<<< orphan*/ * Lang3Entries; int /*<<< orphan*/  Lang3Directory; int /*<<< orphan*/ * Lang2Entries; int /*<<< orphan*/  Lang2Directory; int /*<<< orphan*/ * Lang1Entries; int /*<<< orphan*/  Lang1Directory; int /*<<< orphan*/ * Name2Entries; int /*<<< orphan*/  Name2Directory; int /*<<< orphan*/ * Name1Entries; int /*<<< orphan*/  Name1Directory; int /*<<< orphan*/ * TypeEntries; int /*<<< orphan*/  TypeDirectory; scalar_t__ StringIndex; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PTEST_RESOURCES ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeDataEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  InitializeIdEntry (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitializeNamedEntry (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitializeResourceDirectory (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
VOID
InitializeTestResource(
    PVOID ImageBase,
    PTEST_RESOURCES Resource)
{

    memset(Resource->StringBuffer, 0, sizeof(Resource->StringBuffer));
    Resource->StringIndex = 0;

    InitializeResourceDirectory(&Resource->TypeDirectory, 0, 2);
    InitializeIdEntry(Resource, &Resource->TypeEntries[0], 1, &Resource->Name1Directory);
    InitializeIdEntry(Resource, &Resource->TypeEntries[1], 2, &Resource->Name2Directory);

    InitializeResourceDirectory(&Resource->Name1Directory, 1, 1);
    InitializeNamedEntry(Resource, &Resource->Name1Entries[0], L"TEST", &Resource->Lang1Directory);
    InitializeIdEntry(Resource, &Resource->Name1Entries[1], 7, &Resource->Lang2Directory);

    InitializeResourceDirectory(&Resource->Name2Directory, 2, 0);
    InitializeNamedEntry(Resource, &Resource->Name2Entries[0], L"LOL", &Resource->Lang3Directory);
    InitializeNamedEntry(Resource, &Resource->Name2Entries[1], L"xD", &Resource->Lang4Directory);

    InitializeResourceDirectory(&Resource->Lang1Directory, 0, 2);
    InitializeIdEntry(Resource, &Resource->Lang1Entries[0], 0x409, &Resource->DataEntries[0]);
    InitializeIdEntry(Resource, &Resource->Lang1Entries[1], 0x407, &Resource->DataEntries[1]);

    InitializeResourceDirectory(&Resource->Lang2Directory, 0, 2);
    InitializeIdEntry(Resource, &Resource->Lang2Entries[0], 0x408, &Resource->DataEntries[2]);
    InitializeIdEntry(Resource, &Resource->Lang2Entries[1], 0x406, &Resource->DataEntries[3]);

    InitializeResourceDirectory(&Resource->Lang3Directory, 0, 2);
    InitializeIdEntry(Resource, &Resource->Lang3Entries[0], 0x405, &Resource->DataEntries[4]);
    InitializeIdEntry(Resource, &Resource->Lang3Entries[1], 0x403, &Resource->DataEntries[5]);

    InitializeResourceDirectory(&Resource->Lang4Directory, 0, 2);
    InitializeIdEntry(Resource, &Resource->Lang4Entries[0], 0x402, &Resource->DataEntries[6]);
    InitializeIdEntry(Resource, &Resource->Lang4Entries[1], 0x404, &Resource->DataEntries[7]);

    InitializeDataEntry(ImageBase, &Resource->DataEntries[0], Resource->StringBuffer + 0, 2);
    InitializeDataEntry(ImageBase, &Resource->DataEntries[1], Resource->StringBuffer + 2, 4);
    InitializeDataEntry(ImageBase, &Resource->DataEntries[2], Resource->StringBuffer + 4, 6);
    InitializeDataEntry(ImageBase, &Resource->DataEntries[3], Resource->StringBuffer + 6, 8);
    InitializeDataEntry(ImageBase, &Resource->DataEntries[4], Resource->StringBuffer + 8, 10);
    InitializeDataEntry(ImageBase, &Resource->DataEntries[5], Resource->StringBuffer + 10, 12);
    InitializeDataEntry(ImageBase, &Resource->DataEntries[6], Resource->StringBuffer + 12, 14);
    InitializeDataEntry(ImageBase, &Resource->DataEntries[7], Resource->StringBuffer + 14, 16);

}