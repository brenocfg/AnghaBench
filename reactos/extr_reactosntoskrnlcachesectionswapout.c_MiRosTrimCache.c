#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_8__ {struct TYPE_8__* Flink; } ;
typedef  scalar_t__* PULONG ;
typedef  int /*<<< orphan*/  PMM_SECTION_SEGMENT ;
typedef  TYPE_1__* PLIST_ENTRY ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  CONTAINING_RECORD (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__) ; 
 int /*<<< orphan*/  InsertTailList (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  IsListEmpty (TYPE_1__*) ; 
 int /*<<< orphan*/  ListOfSegments ; 
 int /*<<< orphan*/  MM_SECTION_SEGMENT ; 
 scalar_t__ MiCacheEvictPages (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__ MiSegmentList ; 
 int /*<<< orphan*/  RemoveEntryList (TYPE_1__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
MiRosTrimCache(ULONG Target,
               ULONG Priority,
               PULONG NrFreed)
{
    ULONG Freed;
    PLIST_ENTRY Entry;
    PMM_SECTION_SEGMENT Segment;
    *NrFreed = 0;

    DPRINT1("Need to trim %lu cache pages\n", Target);
    for (Entry = MiSegmentList.Flink;
         *NrFreed < Target && Entry != &MiSegmentList;
         Entry = Entry->Flink) {
        Segment = CONTAINING_RECORD(Entry, MM_SECTION_SEGMENT, ListOfSegments);
        /* Defer to MM to try recovering pages from it */
        Freed = MiCacheEvictPages(Segment, Target);
        *NrFreed += Freed;
    }
    DPRINT1("Evicted %lu cache pages\n", Target);

    if (!IsListEmpty(&MiSegmentList)) {
        Entry = MiSegmentList.Flink;
        RemoveEntryList(Entry);
        InsertTailList(&MiSegmentList, Entry);
    }

    return STATUS_SUCCESS;
}